#pragma once
class GameNetAgent;
class ControllerService;
class GameApp :
    public App {
  public:
    GameApp(int argc, char* argv[]);
    ~GameApp();
  private:
  private:
    GameNetAgent* netAgent_;
  protected:
    virtual void archive() override;
    virtual const vector<const DBTableDefine*>& getTableDefines() const override;
    virtual void mainLoop() override;
    virtual void addExternServices() override;
};

