using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

public class ConfigService: GameFrame.Service<ConfigService> {
    public override IEnumerator Start() {
        CSVParser.loader = LoadConfig;
        yield return LoadConfigs();
    }
    public override string GetTipText() {
        return "加载配置文件";
    }
    TextAsset LoadConfig(string name) {
        return ResourceService.Instance.Load<TextAsset>("Config/" + name);
    }

    public IEnumerator LoadConfigs() {
        Assembly asm = GetType().Assembly;
        var types = asm.GetTypes();
        List<Type> configTypes = new List<Type>();
        foreach (var type in types) {
            if (type.BaseType != null && type.BaseType.IsGenericType && type.BaseType.GetGenericTypeDefinition() == typeof(TableManager<>)) {
                configTypes.Add(type);
            }
        }

        //Progress.Instance.Operator("加载配置中。。。", true);

        for (int i = 0; i < configTypes.Count; ++i) {
            var type = configTypes[i];
            var instance = Activator.CreateInstance(type);
            type.GetField("Instance", BindingFlags.Public | BindingFlags.Static).SetValue(null, instance);
            //Progress.Instance.Update(i + 1, configTypes.Count);
            yield return null;
        }
    }
}
