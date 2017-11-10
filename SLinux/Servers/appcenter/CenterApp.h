#pragma once
class CenterNetAgent;
class HServer;
class CenterApp :
    public App
{
public:
    CenterApp(int narg, char* argv[]);
    ~CenterApp();
    virtual const NetConfig& getNetConfig() override;
    virtual const DBConfig& getDataBaseConfig() override;
    virtual bool parseCommandLine() override;
private:
    CenterNetAgent* mNetAgent;
    HServer* hServer_;
protected:
    virtual void archive() override;

    virtual bool onInitializeEnd() override;

    virtual bool onInitializeNet() override;

    virtual const vector<const DBTableDefine*>& getTableDefines() const override;

};

