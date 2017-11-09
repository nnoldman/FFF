using FairyGUI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class RoleView: View
{
    Login.RolePanel window;

    protected override string GetPackageName()
    {
        return "Login/RolePanel";
    }
    protected override void OnCreate()
    {
        this.goBackWhenClickBG = false;
        this.window = (Login.RolePanel)this.contentPane;
        this.window.enterGame2.onClick.Add(OnCommand);
    }

    protected override void OnCommand(EventContext context)
    {
        if(context.sender == this.window.enterGame2)
        {
            if(LoginSystem.Instance.HasRole())
            {
                Nets.Send(Cmd.CLIENTID.RQEnterGame);
            }
            else
            {
                var cmd = new Cmd.ReqCreateRole();
                cmd.name = this.window.name1.text;
                cmd.sex = 0;
                cmd.job = 1;
                Nets.Send(Cmd.CLIENTID.RQCreateRole, cmd);
            }
        }
    }

    protected override void OnShowMe()
    {
        UpdateUI();
    }

    void SetForEnterGame()
    {
        var role = LoginSystem.Instance.currentRole;
        this.window.name1.text = role.name;
        this.window.name1.asTextInput.enabled = false;
        this.window.enterGame2.title = "进入游戏";
    }

    void SetForCreateRole()
    {
        this.window.name1.asTextInput.enabled = true;
        this.window.enterGame2.title = "创建角色";
    }

    public void UpdateUI()
    {
        if (LoginSystem.Instance.HasRole())
            SetForEnterGame();
        else
            SetForCreateRole();
    }
}
