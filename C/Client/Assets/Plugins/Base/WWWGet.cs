using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
public class WWWGet
{
    private string url_;
    private List<KeyValuePair<string, string>> pairs_ = new List<KeyValuePair<string, string>>();
    private bool dirty_ = false;
    private string address_;
    public WWWGet(string url)
    {
        this.url_ = url;
    }
    public void Add(string key, object value)
    {
        pairs_.Add(new KeyValuePair<string, string>(key, value.ToString()));
        dirty_ = true;
    }

    public string GetAddress()
    {
        if (dirty_)
        {
            dirty_ = false;
            StringBuilder sb = new StringBuilder();
            sb.Append(this.url_);
            for (int i = 0; i < this.pairs_.Count; ++i)
            {
                var pair = pairs_[i];
                sb.Append(i == 0 ? "?" : "&");
                sb.Append(string.Format("{0}={1}", pair.Key, pair.Value));
            }
            address_ = sb.ToString();
        }
        return address_;
    }
}