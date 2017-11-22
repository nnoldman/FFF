#ifndef GameContentService_h__
#define GameContentService_h__

class GameContentService:public  IService<GameContentService> {
  public:
    GameContentService();
    ~GameContentService();
    virtual bool start() override;
    virtual const char * name() override;
};

#endif // GameContentService_h__
