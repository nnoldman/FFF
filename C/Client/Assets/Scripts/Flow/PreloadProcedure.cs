using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GameFrame;

public class PreloadProcedure : GameFrame.Procedure<PreloadProcedure>
{
    public override string GetTipText()
    {
        return "资源预加载。。。";
    }

    public override IEnumerator Start()
    {
        yield return null;
    }
}
