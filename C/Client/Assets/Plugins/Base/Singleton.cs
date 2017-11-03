using System;

public class Singleton<T> where T : new()
{
    protected static T ms_instance;

    protected Singleton()
    {
    }

    public static T Instance
    {
        get
        {
            if(ms_instance == null)
                ms_instance = new T();
            return ms_instance;
        }
    }
}
