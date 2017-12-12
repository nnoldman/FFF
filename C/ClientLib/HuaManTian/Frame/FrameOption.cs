using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

namespace Frame {
public class FrameOption {
    public static class Base {
        /// <summary>
        /// 检测网络等待时长
        /// </summary>
        public static int checkNetReachedSeconds = 30;
        /// <summary>
        /// 检测Wifi等待时长
        /// </summary>
        public static int checkWifiReachedSeconds = 5;
        /// <summary>
        /// 是否允许在蜂窝网络下更新资源
        /// </summary>
        public static bool allowDownloadWithoutWifi = true;
        /// <summary>
        /// 是否允许在没有远程根配置下运行
        /// </summary>
        public static bool allowRunWithoutRemoteRootOption = false;
    }

    public static class Texts {
        public const string retry = "重试";
        public const string goToSetting = "去设置";
        public const string confirm = "确定";
        public const string cancel = "取消";
        public const string netWarning = "网络存在问题，是否重新检测？";
        public const string downloadPackage = "重大版本更新，下载尝鲜吧！";
        public const string goToDownload = "下载新版本";
        public const string exit = "退出";

        public const string goToOpenWifi = "开启Wifi";
        public const string continueDownload = "有的是流量！";
        public const string downloadWarning = "是否允许移动网络下更新资源？";

        public const string updateResourceError = "更新资源错误，是否重试？";

    }
    public enum ResourceConfigFileType {
        ResourceIndex,
    }
    public static class Files {
        public const string abFloder = "ab";
        public readonly static string sdIndexFile = Application.persistentDataPath + "/" + cdnIndexFile;
        public readonly static string sdABFloder = Application.persistentDataPath + "/" + abFloder;
        public const string cdnIndexFile = "index.json";
        public const bool abIndexCompressed = false;
        public const string streamingFilePathFlag = "file://";
    }
}
}
