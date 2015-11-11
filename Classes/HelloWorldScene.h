#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Photon-cpp/inc/LitePeer.h"
#include "SimpleListener.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
	Sprite* _player;
	ExitGames::Lite::LitePeer *peer;
public:
    static cocos2d::Scene* createScene();
    static SimpleListener *lbl;

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void addMonster(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    bool onContactBegan(PhysicsContact &contact);
    void setPeer(ExitGames::Lite::LitePeer *new_peer);
    void setListener(SimpleListener *l) {lbl = l;}
};

#endif // __HELLOWORLD_SCENE_H__
