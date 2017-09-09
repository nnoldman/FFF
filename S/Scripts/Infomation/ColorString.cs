using Data;
using System;
using System.Collections.Generic;
using System.Text;

public class ColorString
{
    public static Color red
    {
        get
        {
            return GameData.QualityColorData.Get(11).color;
        }
    }
    public static Color green
    {
        get
        {
            return GameData.QualityColorData.Get(10).color;
        }
    }
    public static Color grey
    {
        get
        {
            return GameData.QualityColorData.Get(0).color;
        }
    }

    public Color color
    {
        get
        {
            return _color;
        }
        set
        {
            _color = value;
        }
    }

    public string value
    {
        get
        {
            return Fun.ParseColor_NGUIRGB(_color) + _value + "[-]";
        }
        set
        {
            _value = value;
        }
    }
    public string rawValue
    {
        get
        {
            return _value;
        }
        set
        {
            _value = value;
        }
    }

    public string colorHeaderString
    {
        get
        {
            return Fun.ParseColor_NGUIRGB(_color) + _value;
        }
    }

    public static implicit operator string(ColorString str)
    {
        return str.value;
    }

    Color _color = Color.white;
    string _value = string.Empty;
}
