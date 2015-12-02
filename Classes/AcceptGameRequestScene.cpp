#include "AcceptGameRequestScene.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
#include "GameLogic.h"
#include "ChooseOpponentScene.h"

using namespace quoridor;
using namespace cocos2d;
using namespace std;

AcceptGameRequestScene* AcceptGameRequestScene::createScene(string &opponent)
{
    // 'scene' is an autorelease object
    auto scene = AcceptGameRequestScene::create();
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    auto ui_adapter = GameLogic::getUIAdapter();

    string label_text = string("Request from ") + opponent;
    Label* question_label = Label::create(label_text, "arial.ttf", 10);
    question_label->setPosition(Vec2(visibleSize.width / 2, 3 * visibleSize.height / 4));
    scene->addChild(question_label);

    Vector<MenuItem*> items;

    MenuItemFont* yes_item = MenuItemFont::create("Yes", [=](Ref* sender) {
    	ui_adapter->acceptGameRequest(true);
    });
    MenuItemFont* no_item = MenuItemFont::create("No", [=](Ref* sender) {
    	ui_adapter->acceptGameRequest(false);
    });

    items.pushBack(yes_item);
    items.pushBack(no_item);

    auto menu = Menu::createWithArray(items);
    menu->alignItemsVertically();
    scene->addChild(menu);
    // return the scene
    return scene;
}
