#pragma once
class GameNetAgent;
class GameControllers;
class GameApp :
    public App {
  public:
    GameApp(int argc, char* argv[]);
    ~GameApp();
    virtual const NetConfig& getNetConfig() override;
    virtual const DBConfig& getDataBaseConfig() override;
    virtual bool parseCommandLine() override;
  private:
    int serverID_;
  private:
    GameNetAgent* netAgent_;
    GameControllers* controllers_;
  protected:
    virtual void archive() override;
    virtual bool onInitializeEnd() override;
    virtual bool onInitializeNet() override;
    virtual const vector<const DBTableDefine*>& getTableDefines() const override;
    virtual bool loadGameConfig() override;

    virtual void mainLoop() override;

};

