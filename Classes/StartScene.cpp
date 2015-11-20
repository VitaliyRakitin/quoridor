#include "StartScene.h"
#include "UIAdapter.h"
#include "GameLogic.h"

using namespace cocos2d;
using namespace quoridor;

StartScene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = StartScene::create();
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    auto ui_adapter = GameLogic::getUIAdapter();

    auto localGameItem = MenuItemFont::create("Local Game");
    auto networkGameItem = MenuItemFont::create("Network Game",
    [=](Ref* sender){
    	ui_adapter->onNetworkGameChosen();
    });
    Vector<MenuItem*> items;
    items.pushBack(localGameItem);
    items.pushBack(networkGameItem);
    auto menu = Menu::createWithArray(items);
    menu->alignItemsVertically();
    scene->addChild(menu);

    return scene;
}