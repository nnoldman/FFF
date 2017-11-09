using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum GameEventID
{
    GameBaseStart = 100,

    OnMessageChat,
    OnMessageTV,

    OnObjectAdd,
    OnObjectSync,
    OnObjectDelete,
    OnObjectMove,
    GameBaseEnd = 900,


    PropertyStart = 10000,
    PropertyEnd = PropertyStart + 2000,
}


