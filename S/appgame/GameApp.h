#pragma once
class CenterNetAgent;
class GameApp :
    public App
{
public:
    GameApp(int narg, const char** args);
    ~GameApp();
    virtual const NetConfig& getNetConfig() override;

    virtual const DBConfig& getDataBaseConfig() override;

    virtual bool parseCommandLine() override;

private:
    int serverID_;
private:
    CenterNetAgent* netAgent_;
protected:
    virtual void archive() override;


    virtual bool onInitializeEnd() override;


    virtual bool onInitializeNet() override;

    virtual const vector<const DBTableDefine*>& getTableDefines() const override;
};

