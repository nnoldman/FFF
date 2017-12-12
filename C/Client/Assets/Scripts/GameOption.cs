using Frame;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UnityEngine;

public static class GameOption {


    public static class Flow {
        /// <summary>
        /// 远程根配置
        /// </summary>
        public static string RemoteRootConfigFile = "http://127.0.0.1/huamantian/root.json";
    }


    public static class FairyGUIOption {
        public static string PackagePath = "UI/";
    }
    public static GameServer[] GameServers = new GameServer[] {
        new GameServer(){name = "峥嵘岁月", host = "43.248.102.164", port = 7800, serverID = 1},
        new GameServer(){name = "峥嵘岁月1", host = "127.0.0.1", port = 7801, serverID = 2},
        new GameServer(){name = "峥嵘岁月2", host = "127.0.0.1", port = 7802, serverID = 3},

    };

    public static GameServer GetServer(int serverID) {
        return Array.Find<GameServer>(GameServers, (server) => server.serverID == serverID);
    }

    public static class Gate {
        public static readonly string ProgressWindow = "Gate/GateWindow";
        public static readonly string MessageBoxWindow = "Gate/GateBox";
    }


    public static class LogicData {
        public static readonly string dataPath = "Assets/Resources2/Config/";
    }



    public const string XMLExtension = ".xml";
    public static class FilePath {
        public static string GetRemoteFileByPlatform(string cdnURL, RuntimePlatform platform, FrameOption.ResourceConfigFileType fileType) {
            string ret = System.IO.Path.Combine(cdnURL, GetPlatformName(platform));
            ret = System.IO.Path.Combine(ret, GetResourceConfigFileName(fileType));
            ret.Replace('\\', '/');
            return ret;
        }
        public static string GetRemoteFileByPlatform(string cdnURL, RuntimePlatform platform, string fileName) {
            string ret = System.IO.Path.Combine(cdnURL, GetPlatformName(platform));
            ret = System.IO.Path.Combine(ret, fileName);
            ret.Replace('\\', '/');
            return ret;
        }
        public static string GetPlatformName(RuntimePlatform platform) {
            string ret = string.Empty;
            switch (platform) {
            case RuntimePlatform.OSXEditor:
                break;
            case RuntimePlatform.OSXPlayer:
                break;
            case RuntimePlatform.WindowsPlayer:
                break;
            case RuntimePlatform.OSXWebPlayer:
                break;
            case RuntimePlatform.OSXDashboardPlayer:
                break;
            case RuntimePlatform.WindowsWebPlayer:
                break;
            case RuntimePlatform.WindowsEditor:
                break;
            case RuntimePlatform.IPhonePlayer: {
                ret = "ios";
            }
            break;
            case RuntimePlatform.PS3:
                break;
            case RuntimePlatform.XBOX360:
                break;
            case RuntimePlatform.Android: {
                ret = "android";
            }
            break;
            case RuntimePlatform.LinuxPlayer:
                break;
            case RuntimePlatform.WebGLPlayer:
                break;
            case RuntimePlatform.WP8Player:
                break;
            case RuntimePlatform.TizenPlayer:
                break;
            case RuntimePlatform.PSP2:
                break;
            case RuntimePlatform.PS4:
                break;
            case RuntimePlatform.PSM:
                break;
            case RuntimePlatform.XboxOne:
                break;
            case RuntimePlatform.SamsungTVPlayer:
                break;
            case RuntimePlatform.WiiU:
                break;
            case RuntimePlatform.tvOS:
                break;
            default:
                break;

            }
            return ret;
        }
        public static string GetResourceConfigFileName(FrameOption.ResourceConfigFileType fileType) {
            string ret = string.Empty;
            switch (fileType) {
            case FrameOption.ResourceConfigFileType.ResourceIndex: {
                ret = Frame.FrameOption.Files.cdnIndexFile;
            }
            break;
            default:
                break;
            }
            return ret;
        }
        public static string GetSDFile(string fileName) {
            return Path.Combine(Application.persistentDataPath, fileName);
        }
        public static string GetStreamFile(string fileName) {
            var path = Path.Combine(Application.streamingAssetsPath, fileName);
            if (Application.platform != RuntimePlatform.Android)
                path = String.Concat(FrameOption.Files.streamingFilePathFlag, path);
            return path;
        }
        public static string GetSDFile(FrameOption.ResourceConfigFileType fileType) {
            return GetSDFile(GetResourceConfigFileName(fileType));
        }
        public static string GetStreamFile(FrameOption.ResourceConfigFileType fileType) {
            return GetStreamFile(GetResourceConfigFileName(fileType));
        }
    }

    public static class Audit {
        public static int ClientVersion = 10;

        public static readonly string appURL = "https://itunes.apple.com/cn/app/id1256263914?l=zh&ls=1&mt=8";

        private static readonly string sAuditCenterAppURL = "http://yjqk.ts1.tianyouxi.com/mazeserver.php";
        private static readonly string sReleaseCenterAppURL = "http://120.24.183.34/version/maze20171024/mazeserver.php";


        private static readonly string sAuditStoreVertifyURL = "http://yjqk.ts1.tianyouxi.com:15023/?";
        private static readonly string sReleaseStoreVertifyURL = "http://120.24.183.34:15023/?";

        public static readonly string sandBoxVertifyReciptURL = "https://sandbox.itunes.apple.com/verifyReceipt";
        public static readonly string releaseVertifyReciptURL = "https://buy.itunes.apple.com/verifyReceipt";

        public const int appID = 1256263914;
        public const string domain = "com.tryit.world";
        /// <summary>
        /// 是否处于审核阶段
        /// </summary>
        public static bool isAuditing = false;
        public static string centerAppURL {
            get {
                return isAuditing ? sAuditCenterAppURL : sReleaseCenterAppURL;
            }
        }

        public static string appStoreVertifyURL {
            get {
                return isAuditing ? sAuditStoreVertifyURL : sReleaseStoreVertifyURL;
            }
        }

        public static bool shouldRestoreTransactions = true;
    }
    public static class Updata {
        //审核阶段不走该流程
        //public static readonly string ConfigURL = "http://120.24.183.34/version/maze20171024/config/urlconfig.json";
        public static readonly string ConfigURL = "http://www.ffxyx.com";

    }

    public static class BuildOption {
        public static string Path2AssetName(string path) {
            return "assets/resources2/" + path.ToLower();
        }
        public static string GenerateABNameByPath(string relativeName) {
            //string name = Path.GetFileNameWithoutExtension(relativeName).ToLower() + "_";
            string name = "ab_" + relativeName.Replace("\\", "/").ToLower().GetHashCode().ToString();
            return name;
        }
        public const string build_floder = "Build";

        public const string ConfigFloder = "Config/";
        public const string NavigationFloder = ConfigFloder + "Map/";
        public const string MapObjectsFloder = ConfigFloder + "Map/";

        public const string URL_CDNKey = "cdn";
        public const string URL_LoginServers = "login_servers";
        public const string URL_LatelyServer = "lately_srever";
        public const string URL_App = "app_url";

        public const string ASSET_FILE_HEAD = "file://";

        public readonly static string abDefinePathFile = build_floder + "/" + "ab_define.json";
        public readonly static string abDependenceFile = build_floder + "/" + "dependences.json";
        public readonly static string innerDependenceFile = build_floder + "/" + "inner_dependences.json";
        //ABName-resources
        public readonly static string abNamesFile = build_floder + "/" + "names.json";
        //Resource-ABName
        public readonly static string abIndexFile = "index.json";
        public readonly static string abVersionFile = "version.json";



        public readonly static string localABFloder = build_floder + "/assets/";

        public readonly static string ExternResourceFloder = "Resources2/";
        public readonly static string ExternLuaFloder = "ToLua/Lua";
        public readonly static string LuaPath = ExternResourceFloder + ExternLuaFloder;
        public readonly static string abResourceAssetFloder = "Assets/" + ExternResourceFloder;

        public readonly static string ToLuaAssetPath = "/Resources2/3rd/ToLua";
    }
}
