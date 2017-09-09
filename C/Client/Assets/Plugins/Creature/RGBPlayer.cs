using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public class RGBPlayer : RGBCreature, IMoveBase {
    public RGBEquip equip;

    public void MoveTo(Vector3 targetPosition) {
        throw new Exception("The method or operation is not implemented.");
    }
}
