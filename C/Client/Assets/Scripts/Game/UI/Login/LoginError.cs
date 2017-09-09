using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public enum LOGIN_RETURN_CODE  {
    LOGIN_RETURN_SUCESS            = 0,
    LOGIN_RETURN_VERSIONERROR       = 1, // 版本错误
    LOGIN_RETURN_GATEWAYNOTAVAILABLE = 2, // 服务器维护中
    LOGIN_RETURN_CHARNAMEREPEAT = 3, // 角色名称重复
    LOGIN_RETURN_USERDATANOEXIST = 4, // 用户档案不存在
    LOGIN_RETURN_TIMEOUT = 5, // 连接超时
    LOGIN_RETURN_LOCK = 6, // 帐号被锁定
    LOGIN_RETURN_USER_TOZONE = 7, //角色已登录战区, 不允许创建角色
    LOGIN_RETURN_BUSY = 8, //服务器繁忙
    LOGIN_RETURN_FORBID = 9, //帐号被封停
    LOGIN_RETURN_NO_FREENAME = 10, // 没有可用名称
};
