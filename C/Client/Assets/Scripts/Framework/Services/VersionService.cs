using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using UnityEngine;
using System.IO;
using System.Collections;
using System.Threading;

namespace Frame {
public enum UpdateState {
    None,
    WaitForNet,
    CheckWifi,
    ReadRemoteConfig,
    ReadRemoteIndex,
    ReadStreaming,
    ReadSD,
    ExportToSD,
    WriteIndexToSD,
    DownloadIncrements,
    DownloadPackage,
    Sucess,
}

public class VersionService : Service<VersionService> {
    private RemoteRootOption remoteOption_ = new RemoteRootOption();
    private AssetBundleIndex indexRemote_;
    private AssetBundleIndex indexStreaming_;
    private AssetBundleIndex indexSD_;

    private bool remoteRootOptionChecked_ = false;

    protected override IEnumerator OnStart() {
        this.SetTargetState((int)UpdateState.Sucess);
        {
            var procedure = new WaitForNetProcedure();
            procedure.name = "检测网络";
            AddProcedure(UpdateState.None, UpdateState.WaitForNet, procedure);
        }

        {
            var procedure = new DownLoadFileProcedure();
            procedure.name = "检测网络成功，读取streaming信息";
            procedure.getURL = () => GameOption.FilePath.GetStreamFile(FrameOption.ResourceConfigFileType.ResourceIndex);
            procedure.contentHandler = (reponse) => {
                indexStreaming_ = JsonSeriazlier.From<AssetBundleIndex>(reponse.text, Frame.FrameOption.Files.abIndexCompressed);
            };
            procedure.callback = ReadSDIndex;
            AddProcedure(UpdateState.WaitForNet, UpdateState.ReadStreaming, procedure);
        }

        {
#if UNITY_EDITOR
            var procedure = new Procedure();
            procedure.name = "Editor Procedure";
            procedure.canStart = () => !indexStreaming_;
            AddProcedure(UpdateState.ReadStreaming, UpdateState.Sucess, procedure);
#endif
        }

        {
            var procedure = new DownloadFilesProcedure();
            procedure.getURLs = () => GetStreamABURLs();
            procedure.name = "ExportToSD";
            procedure.canStart = () => !indexSD_ || (indexStreaming_ && indexStreaming_.version.HigherThan(indexSD_.version));
            procedure.contentHandler = SaveFileToSD;
            procedure.callback = SaveStreamingInfoToSD;
            AddProcedure(UpdateState.ReadStreaming, UpdateState.ExportToSD, procedure);
        }
        {
            var procedure = new DownloadRemoteRootOptionProcedure();
            procedure.name = "下载远程配置";
            procedure.getURL = () => GameOption.Flow.RemoteRootConfigFile;
            procedure.contentHandler = (reponse) => remoteOption_ = JsonSeriazlier.From<RemoteRootOption>(reponse.text);
            procedure.canStart = () => indexSD_ && !indexStreaming_.version.HigherThan(indexSD_.version);
            procedure.callback = () => {
                this.remoteRootOptionChecked_ = true;
            };
            AddProcedure(UpdateState.ReadStreaming, UpdateState.ReadRemoteConfig, procedure);
        }

        {
            var procedure = new DownloadRemoteRootOptionProcedure();
            procedure.name = "下载远程配置";
            procedure.getURL = () => GameOption.Flow.RemoteRootConfigFile;
            procedure.contentHandler = (reponse) => remoteOption_ = JsonSeriazlier.From<RemoteRootOption>(reponse.text);
            procedure.canStart = () => indexSD_ && !indexStreaming_.version.HigherThan(indexSD_.version);
            procedure.callback = () => {
                this.remoteRootOptionChecked_ = true;
            };
            AddProcedure(UpdateState.ExportToSD, UpdateState.ReadRemoteConfig, procedure);
        }

        {
            var procedure = new DownLoadPackage();
            procedure.name = "下载新版本";
            procedure.canStart = () => remoteOption_
                                 && !string.IsNullOrEmpty(remoteOption_.cdn)
                                 && remoteOption_.CurrentVersion().ProgramHigherThan(indexStreaming_.version)
                                 ;
            procedure.queryState = () => ProduceState.Running;
            AddProcedure(UpdateState.ReadRemoteConfig, UpdateState.DownloadPackage, procedure);
        }

        {
            var procedure = new DownLoadFileProcedure();
            procedure.name = "ReadRemoteIndex";
            procedure.canStart = () => remoteOption_ && remoteOption_.CurrentVersion().HigherThan(indexSD_.version);
            procedure.contentHandler = (reponse) => indexRemote_ = JsonSeriazlier.From<AssetBundleIndex>(reponse.text);
            AddProcedure(UpdateState.ReadRemoteConfig, UpdateState.ReadRemoteIndex, procedure);
        }

        {
            //读取远程版本信息后，如果资源版本较高，如果不允许直接下载就检测Wifi
            var procedure = new WaitForWifiProcedure();
            procedure.name = "检测Wifi";
            procedure.canStart = () => !FrameOption.Base.allowDownloadWithoutWifi && indexRemote_.version && indexRemote_.version.ResourceHigherThan(indexSD_.version);
            AddProcedure(UpdateState.ReadRemoteIndex, UpdateState.CheckWifi, procedure);
        }

        {
            //读取远程版本信息后，如果资源版本较高，如果允许直接下载DownloadIncrements
            var procedure = new DownloadFilesProcedure();
            procedure.name = "DownloadIncrements";
            procedure.getURLs = GetIncrementABUrls;
            procedure.contentHandler = SaveFileToSD;
            procedure.canStart = () => FrameOption.Base.allowDownloadWithoutWifi && remoteOption_ && remoteOption_.CurrentVersion().ResourceHigherThan(indexSD_.version);
            AddProcedure(UpdateState.ReadRemoteIndex, UpdateState.DownloadIncrements, procedure);
        }

        {
            var procedure = new Procedure();
            procedure.name = "Sucess";
            procedure.canStart = () => remoteRootOptionChecked_
                                 && (!indexRemote_ || indexRemote_.version.Equals(indexSD_.version))
                                 ;
            AddProcedure(UpdateState.ReadRemoteConfig, UpdateState.Sucess, procedure);
        }

        {
            var procedure = new DownloadFilesProcedure();
            procedure.name = "DownloadIncrements";
            procedure.getURLs = GetIncrementABUrls;
            procedure.contentHandler = SaveFileToSD;
            procedure.canStart = () => FrameOption.Base.allowDownloadWithoutWifi || Application.internetReachability == NetworkReachability.ReachableViaLocalAreaNetwork;
            AddProcedure(UpdateState.CheckWifi, UpdateState.DownloadIncrements, procedure);
        }

        {
            //检测Wifi成功，下载更新
            var procedure = new Procedure();
            procedure.name = "UpdateState.Sucess";
            AddProcedure(UpdateState.DownloadIncrements, UpdateState.Sucess, procedure);
        }
        yield return null;
    }


    void AddProcedure(UpdateState from, UpdateState to, Procedure procedure) {
        this.AddProcedure((int)from, (int)to, procedure);
    }

    void ProcessVersionError(UpdateState errorState) {

    }

    public List<URLFile> GetStreamABURLs() {
        var urls = new List<URLFile>();
        foreach (var info in indexStreaming_.files) {
            URLFile url = new URLFile();
            url.url = GameOption.FilePath.GetStreamFile(Frame.Helper.CombineWithSlash(Frame.FrameOption.Files.abFloder, info.name));
            url.size = info.size;
            urls.Add(url);
        }
        return urls;
    }

    void ReadSDIndex() {
        indexSD_ = Frame.JsonSeriazlier.LoadFrom<Frame.AssetBundleIndex>(GameOption.FilePath.GetSDFile(
                       Frame.FrameOption.ResourceConfigFileType.ResourceIndex), Frame.FrameOption.Files.abIndexCompressed);
    }
    void SaveStreamingInfoToSD() {
        indexSD_ = indexStreaming_;
        Frame.Helper.SaveJsonObject(indexSD_
                                    , GameOption.FilePath.GetSDFile(FrameOption.Files.cdnIndexFile)
                                    , FrameOption.Files.abIndexCompressed);
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
            Debug.LogWarning(exc.Message);
        }
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
    List<URLFile> GetIncrementABUrls() {
        var remoteABFloader = GameOption.FilePath.GetRemoteFileByPlatform(remoteOption_.cdn, Application.platform
                              , Frame.FrameOption.Files.abFloder);

        AssetBundleIndex incrementList = GetIncrementResourceList(indexSD_, indexRemote_);
        List<URLFile> ret = new List<URLFile>();
        for (int i = 0; i < incrementList.files.Count; ++i) {
            var info = incrementList.files[i];
            URLFile urlFile = new URLFile();
            urlFile.url = Frame.Helper.CombineWithSlash(false, remoteABFloader, info.name);
            urlFile.size = info.size;
            ret.Add(urlFile);
        }
        return ret;
    }
    public override string GetTipText() {
        return "版本更新检测中。。。";
    }

    public override string GetStateDescription(int state) {
        return ((UpdateState)state).ToString();
    }
}
}
