#include "LogInScene.h"
#include "ui/CocosGUI.h"
#include <string>
#include "GameLogic.h"

using namespace quoridor;
using namespace cocos2d;

LogInScene* LogInScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = LogInScene::create();
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    auto ui_adapter = GameLogic::getUIAdapter();

    /*
    Label *label1 = Label::createWithSystemFont("Enter your name", "Arial", 20);
    label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    scene->addChild(label1);
    */

    ui::TextField *textField = ui::TextField::create("Enter username", "Arial", 30);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    scene->addChild(textField);


    auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
    button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 35));
    button->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
    	if (type == ui::Widget::TouchEventType::ENDED) {
    		std::string text = textField->getStringValue();
    		cocos2d::log("GRINLOG: button clicked %s", text.c_str());
    		ui_adapter->logIn(text);
    	}
    });

    scene->addChild(button);
    // return the scene
    return scene;
}
