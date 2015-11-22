#include "ChooseOpponentScene.h"
#include "UIAdapter.h"
#include "GameLogic.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace quoridor;
using namespace std;

ChooseOpponentScene* ChooseOpponentScene::createScene(vector<string>& all_players)
{
	// 'scene' is an autorelease object
	cocos2d::log("GRINLOG: create ChooseOpponentScene");
	auto scene = ChooseOpponentScene::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	MenuItemFont::setFontName("Marker Felt.ttf");
	Vector<MenuItem*> items;

    for (auto player = all_players.begin(); player < all_players.end(); player++) {
    	auto item = MenuItemFont::create(player->c_str());
    	items.pushBack(item);
    }

    auto menu = Menu::createWithArray(items);
    menu->alignItemsVertically();
    scene->addChild(menu);

    /*
	auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
	button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 35));
	button->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			cocos2d::log("GRINLOG: button clicked");
		}
	});
	

	scene->addChild(button);


	auto x = Label::create("Hi, world!", "Marker Felt.ttf", 20);
	x->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	scene->addChild(x);
	*/
	cocos2d::log("GRINLOG: create ChooseOpponentScene all done");
	return scene;
}

