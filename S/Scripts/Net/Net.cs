using DataBase;

public class Net : ScriptObject
{
    public void OnMessage(byte[] msg)
    {
        System.Console.WriteLine("ProtoBufferLength:" + msg.Length);
    }

    public Net()
    {
        Instance = this;
    }

    static void Send(byte[] msg)
    {
        if (null == Instance)
            return;
    }

    public static Net Instance;
}