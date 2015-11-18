#include "LogInScene.h"
#include "ui/CocosGUI.h""

using namespace quoridor;
using namespace cocos2d;

LogInScene* LogInScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = LogInScene::create();
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();

    /*
    Label *label1 = Label::createWithSystemFont("Enter your name", "Arial", 20);
    label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    scene->addChild(label1);
    */

    auto textField = ui::TextField::create("Enter username", "Arial", 30);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    scene->addChild(textField);
    // return the scene
    return scene;
}
