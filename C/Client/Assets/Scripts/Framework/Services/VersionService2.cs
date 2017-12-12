using System;
using Frame;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using UnityEngine;
using System.IO;
using System.Collections;
using System.Threading;



public class VersionService2 : Frame.Service<VersionService2> {
    public enum UpdateState {
        None,
        WaitForNet,
        CheckWifi,
        WaitForWifi,
        GetLocalAddressConfig,
        ReadRemoteConfig,
        ReadRemoteVersion,
        ReadRemoteIndex,
        ReadStreamingVersion,
        ReadStreaming,
        ReadSD,
        ExportToSD,
        WriteIndexToSD,
        DownloadIncrements,
        DownloadPackage,
        Sucess,
    }
    public override string GetTipText() {
        return "版本检测中。。。";
    }

    public bool running = true;
    public bool allowDownloadWithoutWifi = false;
    UpdateState state;

    public string errorContent {
        get;
        private set;
    }
    public LoadingError errorCode {
        get {
            return mErrorCode;
        }
        set {
            mErrorCode = value;
        }
    }
    public Frame.GameEventHandler<string, LoadingError> errorHandler;

    public Action netWaring;
    public Action wifiWaring;

    private int mCheckNetReachedTimes = 0;
    private int mCheckWifiReachedTimes = 0;
    public LoadingError mErrorCode = LoadingError.Success;

    Frame.AssetBundleIndex mIndexRemote;
    Frame.AssetBundleIndex mIndexStreaming;
    Frame.AssetBundleIndex mIndexSD;

    string mURLCDN = string.Empty;
    string mURLApp = string.Empty;
    string mURLLoginServers = string.Empty;
    string mURLLatelyServer = string.Empty;

    string mRemoteABFloderURL = string.Empty;
    string mRemoteIndexFileURL = string.Empty;
    string mRemoteVersionFile = string.Empty;

    string mRemoteAddress = string.Empty;

    private Frame.RemoteRootOption remoteOption_ = new Frame.RemoteRootOption();
    private Frame.GameVersion mVersionRemote = new Frame.GameVersion();
    private Frame.GameVersion mVersionSD = new Frame.GameVersion();
    private Frame.GameVersion mVersionStreaming = new Frame.GameVersion();

    private Dictionary<string, ResourceIndex> mIndexMap = new Dictionary<string, ResourceIndex>();

    public string appURL {
        get {
            return mURLApp;
        }
    }

    public string loginServersURL {
        get {
            return mURLLoginServers;
        }
    }

    public string latelyServerURL {
        get {
            return mURLLatelyServer;
        }
    }

    public string localVersion {
        get {
            return mVersionSD == null ? mVersionStreaming.ToString() : mVersionSD.ToString();
        }
    }
    public string remoteVersion {
        get {
            return mVersionRemote.ToString();
        }
    }
    public string cdnURL {
        get {
            return mURLCDN;
        }
    }

    protected override IEnumerator OnStart() {
#if UNITY_EDITOR
        yield return null;
#else
        yield return DoUpdata();
#endif
    }

    public string DownLoadText(string url) {
        try {
            WWW sync = new WWW(url);
            byte[] data = sync.bytes;
            if (data != null)
                return Encoding.UTF8.GetString(data);
            return string.Empty;
        } catch (WebException exc) {
            Debug.LogError(exc.Message);
            return String.Empty;
        }
    }

    public string GetABName(string pathfile) {
        string ret;
        mIndexSD.indexMap.TryGetValue(pathfile.ToLower(), out ret);
        return ret;
    }

    public static string GetFirstLine(string content) {
        int linepos = content.IndexOf("\r\n");
        if (linepos != -1)
            return content.Substring(0, linepos);
        linepos = content.IndexOf("\n");
        return content.Substring(0, linepos);
    }

    public string getStreamingIndexFile {
        get {
            var url = GetStreamPath(Frame.FrameOption.Files.cdnIndexFile);
            return url;
        }
    }


    void Error(string msg, LoadingError error) {
        this.mErrorCode = error;
        this.errorContent = msg;
        if (error != LoadingError.RemoteURLConfigLoadFailedOrEmpty) {
            if (errorHandler != null) {
                errorHandler(msg, error);
            }
        }
    }

    bool Success(bool ok, LoadingError error) {
        if (!ok) {
            Error(errorCode.ToString(), error);
        }
        return ok;
    }
    void SetState(UpdateState state) {
        this.state = state;
    }

    public void RetryNet() {
        mCheckNetReachedTimes = 0;
        SetState(UpdateState.None);
    }

    public void RetryWifi() {
        mCheckWifiReachedTimes = 0;
        SetState(UpdateState.CheckWifi);
    }

    public IEnumerator DoUpdata() {
        while (state != UpdateState.Sucess) {
            switch (state) {
            case UpdateState.None: {
                if (Application.internetReachability == NetworkReachability.NotReachable) {
                    mCheckNetReachedTimes++;
                    if (mCheckNetReachedTimes > 3000) {
                        if (netWaring != null)
                            netWaring.Invoke();
                    }
                    yield return null;
                } else {
                    SetState(UpdateState.WaitForNet);
                }
            }
            break;
            case UpdateState.WaitForNet: {
                if (Application.internetReachability != NetworkReachability.NotReachable)
                    SetState(UpdateState.GetLocalAddressConfig);
                else
                    yield return null;
            }
            break;
            case UpdateState.CheckWifi: {
                if (Application.internetReachability != NetworkReachability.ReachableViaLocalAreaNetwork) {
                    mCheckWifiReachedTimes++;
                    if (mCheckWifiReachedTimes > 3000) {
                        if (wifiWaring != null)
                            wifiWaring.Invoke();
                        SetState(UpdateState.WaitForWifi);
                    }
                    yield return null;
                } else {
                    SetState(UpdateState.WaitForWifi);
                }
            }
            break;
            case UpdateState.WaitForWifi: {
                if (Application.internetReachability == NetworkReachability.ReachableViaLocalAreaNetwork || allowDownloadWithoutWifi) {
                    SetState(UpdateState.DownloadIncrements);
                } else {
                    yield return null;
                }
            }
            break;
            case UpdateState.GetLocalAddressConfig: {
                DoNowStep stepLoadResourceAddr = new DoNowStep();
                stepLoadResourceAddr.name = "加载本地配置";
                stepLoadResourceAddr.onEnd = TryGetAddressConfig;
                stepLoadResourceAddr.exit = () => string.IsNullOrEmpty(mRemoteAddress);
                stepLoadResourceAddr.errorCode = LoadingError.ResourceLoginServerAddressConfigNotExist;
                yield return DoNow(stepLoadResourceAddr);
                SetState(UpdateState.ReadRemoteConfig);
            }
            break;
            case UpdateState.ReadRemoteConfig: {
                LoadOneStep stepGetRemoteConfig = new LoadOneStep();
                stepGetRemoteConfig.name = "获取服务器配置文件";
                stepGetRemoteConfig.getURL = () => mRemoteAddress;
                stepGetRemoteConfig.loadDelegate = TryGetRemoteURLConfig;
                stepGetRemoteConfig.exit = () => string.IsNullOrEmpty(mRemoteVersionFile);
                stepGetRemoteConfig.errorCode = LoadingError.RemoteURLConfigLoadFailedOrEmpty;
                yield return DoOneStep(stepGetRemoteConfig);
                if (mErrorCode == LoadingError.RemoteURLConfigLoadFailedOrEmpty) {
                    Debug.LogWarning("Error URL Config!" + mRemoteVersionFile);
                    SetState(UpdateState.ReadStreamingVersion);
                } else {
                    SetState(UpdateState.ReadRemoteVersion);
                }
            }
            break;
            case UpdateState.ReadRemoteVersion: {
                LoadOneStep stepLoadRemoteVersion = new LoadOneStep();
                stepLoadRemoteVersion.name = "加载服务器版本信息";
                stepLoadRemoteVersion.getURL = () => mRemoteVersionFile;
                stepLoadRemoteVersion.loadDelegate = TryGetVersionFromRemote;
                stepLoadRemoteVersion.exit = () => mVersionRemote == null;
                stepLoadRemoteVersion.errorCode = LoadingError.RemoteVersionLoadFailedOrEmpty;
                yield return DoOneStep(stepLoadRemoteVersion);
                SetState(UpdateState.ReadRemoteIndex);
            }
            break;
            case UpdateState.ReadRemoteIndex: {
                LoadOneStep stepLoadRemoteIndex = new LoadOneStep();
                stepLoadRemoteIndex.name = "加载远程索引信息";
                stepLoadRemoteIndex.loadDelegate = TryGetRemoteIndex;
                stepLoadRemoteIndex.exit = () => false;
                stepLoadRemoteIndex.getURL = () => mRemoteIndexFileURL;
                stepLoadRemoteIndex.errorCode = LoadingError.RemoteIndexLoadFailedOrEmpty;
                yield return DoOneStep(stepLoadRemoteIndex);
                SetState(UpdateState.ReadStreamingVersion);
            }
            break;
            case UpdateState.ReadStreamingVersion: {
                LoadOneStep stepLoadStreamingVersion = new LoadOneStep();
                stepLoadStreamingVersion.name = "加载Streaming版本信息";
                stepLoadStreamingVersion.loadDelegate = TryGetVersionFromStreamingAsset;
                stepLoadStreamingVersion.exit = () => false;
                //stepLoadStreamingVersion.getURL = () => getStreamingVersionFile;
                yield return DoOneStep(stepLoadStreamingVersion);
                SetState(UpdateState.ReadStreaming);
            }
            break;
            case UpdateState.ReadStreaming: {
                LoadOneStep stepLoadStreamingIndex = new LoadOneStep();
                stepLoadStreamingIndex.name = "加载Streaming索引信息";
                stepLoadStreamingIndex.loadDelegate = TryGetStreamingIndex;
                stepLoadStreamingIndex.exit = () => false;
                stepLoadStreamingIndex.getURL = () => getStreamingIndexFile;
                yield return DoOneStep(stepLoadStreamingIndex);
                SetState(UpdateState.ReadSD);
            }
            break;
            case UpdateState.ReadSD: {
                DoNowStep stepLoadSDInfo = new DoNowStep();
                stepLoadSDInfo.name = "加载SD版本信息";
                stepLoadSDInfo.onEnd = TryGetInfoFromSD;
                stepLoadSDInfo.exit = () => false;
                yield return DoNow(stepLoadSDInfo);

                if (mVersionRemote.ProgramHigherThan(mVersionStreaming)) {
                    SetState(UpdateState.DownloadPackage);
                } else {
                    if (mVersionSD == null) {
                        SetState(UpdateState.ExportToSD);
                    } else if (mVersionRemote.HigherThan(mVersionSD)) {
                        SetState(UpdateState.DownloadIncrements);
                        //SetState(UpdateState.CheckWifi);
                    } else if (mVersionStreaming.HigherThan(mVersionSD)) {
                        SetState(UpdateState.ExportToSD);
                    } else {
                        SetState(UpdateState.Sucess);
                    }
                }
            }
            break;
            case UpdateState.ExportToSD: {
                LoadBeatchStep stepExportToSD = new LoadBeatchStep();
                stepExportToSD.name = "解压文件中，请不要关闭游戏，此过程不消耗流量";
                stepExportToSD.exit = () => false;
                stepExportToSD.getURLs = GetStreamABURLs;
                stepExportToSD.onEnd = SaveStreamingInfoToSD;
                stepExportToSD.errorCode = LoadingError.SDSaveVersionOrIndexFailed;
                stepExportToSD.loadDelegate = SaveFileToSD;
                yield return LoadBeatch(stepExportToSD);
                SetState(UpdateState.ReadSD);
            }
            break;
            case UpdateState.DownloadIncrements: {
                LoadBeatchStep stepLoadIncrement = new LoadBeatchStep();
                stepLoadIncrement.name = "更新中，请不要关闭游戏";
                stepLoadIncrement.exit = () => false;
                stepLoadIncrement.getURLs = GetIncrementABUrls;
                stepLoadIncrement.onEnd = SaveRemoteInfoToSD;
                stepLoadIncrement.errorCode = LoadingError.SDSaveVersionOrIndexFailed;
                stepLoadIncrement.loadDelegate = SaveFileToSD;
                yield return LoadBeatch(stepLoadIncrement);
                SetState(UpdateState.Sucess);
            }
            break;
            case UpdateState.DownloadPackage: {
                mErrorCode = LoadingError.PackageError;
            }
            break;
            case UpdateState.Sucess:
                break;
            default:
                break;
            }

            if (mErrorCode != LoadingError.Success && mErrorCode != LoadingError.RemoteURLConfigLoadFailedOrEmpty) {
                Error(errorContent, errorCode);
                SetState(UpdateState.None);
                yield break;
            }
        }
    }

    public IEnumerator DoUpdataWithOutCheckResource() {
        while (state != UpdateState.Sucess) {
            switch (state) {
            case UpdateState.None: {
                if (Application.internetReachability == NetworkReachability.NotReachable) {
                    mCheckNetReachedTimes++;
                    if (mCheckNetReachedTimes > 3000) {
                        if (netWaring != null)
                            netWaring.Invoke();
                    }
                    yield return null;
                } else {
                    SetState(UpdateState.WaitForNet);
                }
            }
            break;
            case UpdateState.WaitForNet: {
                if (Application.internetReachability != NetworkReachability.NotReachable) {
                    SetState(UpdateState.Sucess);
                } else
                    yield return null;
            }
            break;
            }

            if (mErrorCode != LoadingError.Success) {
                Error(errorContent, errorCode);
                SetState(UpdateState.None);
                mErrorCode = LoadingError.Success;
                yield break;
            }
        }
    }
    IEnumerator DoNow(DoNowStep current) {
        Frame.Executer.SetProgressText(current.name);
        Frame.Executer.SetProgress(0, 1);
        yield return null;
        if (current.onEnd != null)
            current.onEnd.Invoke();
        if (current.exit != null && current.exit()) {
            Error(current.name, current.errorCode);
            yield break;
        }
        Frame.Executer.SetProgress(1, 1);
        yield return null;
    }

    IEnumerator DoOneStep(LoadOneStep current) {
        Frame.Executer.SetProgressText(current.name);
        yield return 0;
        LoadOneStep theStep = (LoadOneStep)current;
        string url = theStep.getURL();
        Debug.Log(url);
        Frame.Executer.SetProgress(0, 1, string.Empty);
        WWW www = new WWW(url);
        while (!www.isDone) {
            Frame.Executer.SetProgress((int)(100 * www.progress));
            Thread.Sleep(1);
            yield return null;
        }
        if (!string.IsNullOrEmpty(www.error)) {
            Error(www.error, current.errorCode);
            yield break;
        }
        Frame.Executer.SetProgress(1, 1, string.Empty);
        theStep.loadDelegate(www);
        www.Dispose();

        if (current.exit != null && current.exit()) {
            Error(current.name, current.errorCode);
            yield break;
        }
        yield return null;
    }

    IEnumerator LoadBeatch(LoadBeatchStep current) {
        Frame.Executer.SetProgressText(current.name);
        yield return null;
        LoadBeatchStep beatch = (LoadBeatchStep)current;
        var urlFiles = beatch.getURLs();
        var len = urlFiles.Count;
        int totalSize = 0;
        urlFiles.ForEach((item) => totalSize += item.size);
        int curSize = 0;
        for (int i = 0; i < len; ++i) {
            string url = urlFiles[i].url;
            int size = urlFiles[i].size;
            Debug.Log(url);
            WWW www = new WWW(url);
            while (!www.isDone) {
                Frame.Executer.SetProgress(curSize + (int)(size * www.progress), totalSize);
                Thread.Sleep(1);
                yield return null;
            }
            if (!string.IsNullOrEmpty(www.error)) {
                Error(www.error, current.errorCode);
                yield break;
            }
            curSize += www.bytesDownloaded;
            beatch.loadDelegate(www);
            www.Dispose();

            if (current.onEnd != null)
                current.onEnd();

            if (current.exit != null && current.exit()) {
                Error(current.name, current.errorCode);
                yield break;
            }
            yield return null;
        }
    }

    public List<URLFile> GetStreamABURLs() {
        var urls = new List<URLFile>();
        foreach (var info in mIndexStreaming.files) {
            URLFile url = new URLFile();
            url.url = GetStreamPath(Frame.Helper.CombineWithSlash(Frame.FrameOption.Files.abFloder, info.name));
            url.size = info.size;
            urls.Add(url);
        }
        return urls;
    }

    void SaveFileToSD(WWW www) {
        try {
            string fileName = Path.GetFileName(www.url);
            string sdFile = Frame.Helper.CombineWithSlash(Frame.FrameOption.Files.sdABFloder, fileName);
            if (www.bytes != null && www.bytes.Length != 0) {
                string path = Path.GetDirectoryName(sdFile);
                if (!Directory.Exists(path))
                    Directory.CreateDirectory(path);
                File.WriteAllBytes(sdFile, www.bytes);
                //Zip7Helper.DecompressFileLZMA(www.bytes, sdFile);
            }
        } catch (Exception exc) {
            Error(exc.Message, LoadingError.SDSaveVersionOrIndexFailed);
        }
    }

    void SaveStreamingInfoToSD() {
        mIndexSD = mIndexStreaming;
        Frame.Helper.SaveJsonObject(mIndexSD, GetSDFile(Frame.FrameOption.Files.cdnIndexFile), Frame.FrameOption.Files.abIndexCompressed);
        mVersionSD = mVersionStreaming;
        //Frame.Helper.SaveJsonObject(mVersionSD, GetSDFile(Frame.FrameOption.Files.cdnVersionFile));
    }

    void SaveRemoteInfoToSD() {
        mIndexSD = mIndexRemote;
        Frame.Helper.SaveJsonObject(mIndexSD, GetSDFile(Frame.FrameOption.Files.cdnIndexFile), Frame.FrameOption.Files.abIndexCompressed);
        mVersionSD = mVersionRemote;
        //Frame.Helper.SaveJsonObject(mVersionSD, GetSDFile(Frame.FrameOption.Files.cdnVersionFile));
    }

    public void GoToUpdatePackage() {
        Application.OpenURL(GameOption.Audit.appURL);
    }

    string GetResourceFileContent(string fileName) {
        string filename = Frame.Helper.EnsureNameWithOutExtenision(fileName);
        TextAsset textasset = Resources.Load<TextAsset>(filename);
        return textasset == null ? string.Empty : textasset.text;
    }

    static string GetSDFile(string fileName) {
        return Frame.Helper.CombineWithSlash(Application.persistentDataPath, fileName);
    }

    public string GetStreamPath(string fileName) {
        var Path = Frame.Helper.CombineWithSlash(false, Application.streamingAssetsPath, fileName);
        if (Application.platform != RuntimePlatform.Android)
            Path = String.Concat(FrameOption.Files.streamingFilePathFlag, Path);
        return Path;
    }

    string GetRemoteFileContent(string url) {
        return DownLoadText(url);
    }

    string GetPlatformString() {
        string platform = string.Empty;

        switch (Application.platform) {
        case RuntimePlatform.Android:
        case RuntimePlatform.WindowsEditor: {
            platform = GamePlatform.android.ToString();
        }
        break;
        case RuntimePlatform.IPhonePlayer: {
            platform = GamePlatform.ios.ToString();
        }
        break;
        default: {
            throw new Exception("Unknown Platform!");
        }
        break;
        }
        return platform;
    }

    void TryGetVersionFromRemote(WWW www) {
        mVersionRemote = JsonUtility.FromJson<Frame.GameVersion>(www.text);
        Success(mVersionRemote != null, LoadingError.RemoteVersionLoadFailedOrEmpty);
    }

    void TryGetInfoFromSD() {
        Debug.Log("TryGetVersionFromSD:");
        //mVersionSD = Frame.Helper.LoadJsonObject<Frame.GameVersion>(GetSDFile(Frame.FrameOption.Files.cdnVersionFile));
        mIndexSD = Frame.Helper.LoadJsonObject<AssetBundleIndex>(GetSDFile(Frame.FrameOption.Files.cdnIndexFile), Frame.FrameOption.Files.abIndexCompressed);
    }

    void TryGetVersionFromStreamingAsset(WWW www) {
        mVersionStreaming = JsonUtility.FromJson<Frame.GameVersion>(www.text);
        Success(mVersionStreaming != null, LoadingError.StreamingLoadVersionError);
    }

    void TryGetAddressConfig() {
        mRemoteAddress = GameOption.Updata.ConfigURL;
        //string url = GetResourceFileContent(GameConfig.remoteURLConfigFile);
        //mRemoteAddress = GetFirstLine(url);
    }

    void TryGetRemoteURLConfig(WWW www) {
        var urlConfigContent = www.text;
        remoteOption_ = Frame.JsonSeriazlier.From<Frame.RemoteRootOption>(urlConfigContent);
        Debug.Log("URLConfig:" + www.text);
        if (Success(remoteOption_ != null && remoteOption_.CurrentVersion().main > 0, LoadingError.RemoteURLConfigLoadFailedOrEmpty)) {
            mRemoteABFloderURL = Frame.Helper.CombineWithSlash(false, remoteOption_.cdn, GetPlatformString(), Frame.FrameOption.Files.abFloder);
            mRemoteIndexFileURL = Frame.Helper.CombineWithSlash(false, remoteOption_.cdn, GetPlatformString(), Frame.FrameOption.Files.cdnIndexFile);
            //mRemoteVersionFile = Frame.Helper.CombineWithSlash(false, remoteOption_.cdn, GetPlatformString(), Frame.FrameOption.Files.cdnVersionFile);

            if (!Directory.Exists(Frame.FrameOption.Files.sdABFloder))
                Directory.CreateDirectory(Frame.FrameOption.Files.sdABFloder);
        }
    }


    void TryGetRemoteIndex(WWW www) {
        mIndexRemote = Frame.Helper.FromJsonWithZip<AssetBundleIndex>(www.bytes, Frame.FrameOption.Files.abIndexCompressed);
        Success(mIndexRemote != null, LoadingError.RemoteIndexLoadFailedOrEmpty);
    }
    void TryGetStreamingIndex(WWW www) {
        mIndexStreaming = Frame.Helper.FromJsonWithZip<AssetBundleIndex>(www.bytes, Frame.FrameOption.Files.abIndexCompressed);
        Success(mIndexStreaming != null, LoadingError.StreamingLoadIndexError);
    }

    bool SaveVersionToSD() {
        //mVersionSD = mVersionRemote;
        //return Frame.Helper.SaveJsonObject(mVersionSD, GameOption.BuildOption.sdVersionFile);
        return true;
    }

    List<URLFile> GetIncrementABUrls() {
        AssetBundleIndex incrementList = GetIncrementResourceList(mIndexSD, mIndexRemote);
        List<URLFile> ret = new List<URLFile>();
        for (int i = 0; i < incrementList.files.Count; ++i) {
            var info = incrementList.files[i];
            URLFile urlFile = new URLFile();
            urlFile.url = Frame.Helper.CombineWithSlash(false, mRemoteABFloderURL, info.name);
            urlFile.size = info.size;
            ret.Add(urlFile);
        }
        return ret;
    }

    public AssetBundleIndex GetIncrementResourceList(AssetBundleIndex list0, AssetBundleIndex list1) {
        if (list1 == null)
            return null;

        Dictionary<string, ABFile> map0 = list0 == null ? null : list0.abMap;
        Dictionary<string, ABFile> map1 = list1.abMap;

        AssetBundleIndex incremetList = new AssetBundleIndex();

        foreach (var data in map1) {
            ABFile info = null;

            if (map0 == null || !map0.TryGetValue(data.Key, out info) || info.hash != data.Value.hash) {
                incremetList.files.Add(data.Value);
            }
        }
        return incremetList;
    }

    public ABFile GetAB(string abName) {
        ABFile info;
        mIndexSD.abMap.TryGetValue(abName, out info);
        return info;
    }


}
