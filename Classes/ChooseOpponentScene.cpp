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
	auto ui_adapter = GameLogic::getUIAdapter();

	/*
	Label* chosen_opponent = Label::createWithTTF("", "arial.ttf", 20);
	chosen_opponenet->setPosition(Vec2(3 * visibleSize.width / 4, visibleSize.height / 4));
	scene->addChild(chosen_opponenet);
	 */

	Vector<MenuItem*> items;

	all_players.push_back("Some guy");

	for (auto player = all_players.begin(); player < all_players.end(); player++) {
		MenuItemFont* item = MenuItemFont::create(player->c_str(), [=](Ref* pSender) {
			auto sender = (MenuItemFont*) pSender;
			auto player_name = sender->getName();
			cocos2d::log("GRINLOG: item %s selected", player_name.c_str());
			ui_adapter->onOpponentChosen(player_name);
		});
		item->setName(*player);
		items.pushBack(item);
	}


	auto menu = Menu::createWithArray(items);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2));
	scene->addChild(menu);

	/*
	auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");

	button->setPosition(Vec2(3 * visibleSize.width / 4, 3 * visibleSize.height / 4));

	button->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			cocos2d::log("GRINLOG: button clicked %s");
			chosen_opponent->setString()
		}
	});
	scene->addChild(button);
	 */

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

