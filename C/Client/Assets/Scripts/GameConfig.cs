using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public static class GameConfig
{
    public static class FairyGUIOption
    {
        public static string PackagePath = "UI/";
    }
    public static GameServer[] GameServers = new GameServer[]
    {
        new GameServer(){name = "峥嵘岁月", host = "43.248.102.164", port = 7800, serverID = 1},
        new GameServer(){name = "峥嵘岁月1", host = "127.0.0.1", port = 7801, serverID = 2},
        new GameServer(){name = "峥嵘岁月2", host = "127.0.0.1", port = 7802, serverID = 3},

    };

    public static GameServer GetServer(int serverID)
    {
        return Array.Find<GameServer>(GameServers, (server) => server.serverID == serverID);
    }

    public static class Gate
    {
        public static readonly string ProgressWindow = "Gate/GateWindow";
    }


    public static class LogicData
    {
        public static readonly string dataPath = "Assets/Resources2/Config/";
    }

    public const string XMLExtension = ".xml";


    public static class Audit
    {
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
        public static string centerAppURL
        {
            get
            {
                return isAuditing ? sAuditCenterAppURL : sReleaseCenterAppURL;
            }
        }

        public static string appStoreVertifyURL
        {
            get
            {
                return isAuditing ? sAuditStoreVertifyURL : sReleaseStoreVertifyURL;
            }
        }

        public static bool shouldRestoreTransactions = true;
    }
    public static class Updata
    {
        //审核阶段不走该流程
        //public static readonly string ConfigURL = "http://120.24.183.34/version/maze20171024/config/urlconfig.json";
        public static readonly string ConfigURL = "http://www.ffxyx.com";

    }

    public static class BuildOption
    {
        public static string Path2AssetName(string path)
        {
            return "assets/resources2/" + path.ToLower();
        }
        public static string GenerateABNameByPath(string relativeName)
        {
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

        public const string abFloder = "ab";
        public const string ASSET_FILE_HEAD = "file://";

        public readonly static bool abIndexCompressed = true;

        public readonly static string abDefinePathFile = build_floder + "/" + "ab_define.json";
        public readonly static string abDependenceFile = build_floder + "/" + "dependences.json";
        public readonly static string innerDependenceFile = build_floder + "/" + "inner_dependences.json";
        //ABName-resources
        public readonly static string abNamesFile = build_floder + "/" + "names.json";
        //Resource-ABName
        public readonly static string abIndexFile = "index.json";
        public readonly static string abVersionFile = "version.json";

        public readonly static string sdVersionFile = Application.persistentDataPath + "/" + abVersionFile;
        public readonly static string sdIndexFile = Application.persistentDataPath + "/" + abIndexFile;
        public readonly static string sdABFloder = Application.persistentDataPath + "/" + abFloder;

        public readonly static string localABFloder = build_floder + "/assets/";

        public readonly static string ExternResourceFloder = "Resources2/";
        public readonly static string ExternLuaFloder = "ToLua/Lua";
        public readonly static string LuaPath = ExternResourceFloder + ExternLuaFloder;
        public readonly static string abResourceAssetFloder = "Assets/" + ExternResourceFloder;

        public readonly static string ToLuaAssetPath = "/Resources2/3rd/ToLua";
    }
}
