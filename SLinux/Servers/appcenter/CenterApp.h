#ifndef CenterApp_h__
#define CenterApp_h__
class CenterApp : public App {
  public:
    CenterApp(int narg, char* argv[]);
    ~CenterApp();
  private:
    virtual void archive() override;
    virtual void addExternServices() override;
    virtual const vector<const DBTableDefine*>& getTableDefines() const override;
};

#endif // CenterApp_h__
