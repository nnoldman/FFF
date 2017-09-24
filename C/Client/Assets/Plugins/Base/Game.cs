using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using UnityEngine;

namespace AppCore
{
public class Game
{
    private SceneParam mSceneParam;

    public IEnumerator Start()
    {
        yield return 0;
    }

    public IEnumerator Close()
    {
        yield return null;
    }

    public IEnumerator LoadScene(SceneParam param)
    {
        mSceneParam = param;
        OnSceneClose();
        yield return null;
        OnSceneOpen();
        yield return null;
    }


    public void OnSceneOpen()
    {
    }
    public void OnSceneClose()
    {
    }
    public void OnMapLoaded()
    {
    }
    public void OnHeroReady()
    {
    }

}
}
