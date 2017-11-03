using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

public class GameSystemsProcedure: GameFrame.Procedure<GameSystemsProcedure>
{
    public override IEnumerator Start()
    {
        return InitSystems();
    }
    public override string GetTipText()
    {
        return "初始化游戏系统";
    }
    public IEnumerator InitSystems()
    {
        Assembly asm = GetType().Assembly;
        var types = asm.GetTypes();
        foreach (var type in types)
        {
            if (type.IsSubclassOf(typeof(SystemBase)))
            {
                var instance = Activator.CreateInstance(type);
                var filed = type.GetField("Instance", BindingFlags.Public | BindingFlags.Static);
                if (filed == null)
                {
                    Debug.LogError(string.Format("System {0} does not has Instance!"));
                }
                else
                {
                    filed.SetValue(null, instance);
                    var system = (SystemBase)instance;
                    if (system.timeConsuming)
                        yield return system.Initialize();
                }
            }
        }
    }
}
