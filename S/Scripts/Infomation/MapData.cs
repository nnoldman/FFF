using Data;
using System;
using System.Collections.Generic;


namespace GameData
{
    public class MapData : GameData<MapData>
    {
        public String lightmap ;
        public String lightProbes ;
        public Dictionary<String, bool> modelName ;
        public Color cameraColor ;
        public float cameraFar ;
        public bool fog ;
        public Color fogColor ;
        public FogMode fogMode ;
        public float linearFogStart ;
        public float linearFogEnd ;
        public Color ambientLight ;
        public String sceneName ;

        public List<int> backgroundMusic ;
        public static readonly string fileName = "xml/map_setting";
        //public static Dictionary<int, MapData> dataMap { get; set; }


        public MapData()
        {
            sceneName = "InstanceScene";
        }

    }

    public enum LightType : byte
    {
        /// <summary>
        /// 不加光
        /// </summary>
        None = 0,
        /// <summary>
        /// 普通光
        /// </summary>
        Normal = 1
    }
}