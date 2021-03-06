﻿using UnityEngine;
using System.Collections;
using GameFrame;
using FairyGUI;
using System.Reflection;
using System;
using System.Collections.Generic;

public class NetService : Frame.Service<NetService> {
    private int netQuertyTimes_ = 0;
    private int netQuertyTargetTimes_ = 3000;
    public override string GetTipText() {
        return "初始化网络系统";
    }
    protected override IEnumerator OnStart() {
        while (Application.internetReachability == NetworkReachability.NotReachable && netQuertyTimes_ < netQuertyTargetTimes_) {
            yield return null;
        }
    }
}

