#include "UIAdapter.h"
#include "LogInScene.h"
#include "GameLogic.h"
#include "StartScene.h"
#include "PlayWithBot.h"
#include "ChooseOpponentScene.h"

USING_NS_CC;

using namespace quoridor;
using namespace std;

UIAdapter::UIAdapter() {
}

void UIAdapter::logIn(std::string &username) {
	GameLogic::getInstance()->connect(username);
	cocos2d::log("GRINLOG: UIAdapter::logIn");
}

void UIAdapter::renderLogInScence() {
	auto director = cocos2d::Director::getInstance();
	cur_scene = LogInScene::createScene();
	addLogicTick(cur_scene);
	director->runWithScene(cur_scene);
}

void UIAdapter::start() {
	cur_scene = StartScene::createScene();
	Director::getInstance()->runWithScene(cur_scene);
}

void UIAdapter::onNetworkGameChosen() {
	cur_scene = LogInScene::createScene();
	Director::getInstance()->replaceScene(cur_scene);
}

void UIAdapter::onPlayWithBot() {
	cur_scene = PlayWithBot::createScene();
	Director::getInstance()->replaceScene(cur_scene);
}


void UIAdapter::renderChooseOpponentScene(vector<string>& all_players) {
	cocos2d::log("GRINLOG:UIAdapter::renderChooseOpponentScene");
	for (auto iter = all_players.begin(); iter < all_players.end(); iter++) {
		cocos2d::log("GRINLOG:UIAdapter::renderChooseOpponentScene: %s", iter->c_str());
	}
	cur_scene = ChooseOpponentScene::createScene(all_players);
	cocos2d::log("GRINLOG: ChooseOpponentScene created");
	addTickerToCurrentScene();
	Director::getInstance()->replaceScene(cur_scene);
}

void UIAdapter::addLogicTick(cocos2d::Scene *scene) {
	auto ticker = GameLogic::getTicker();
	if (ticker != nullptr) {
		ticker->removeFromParentAndCleanup(false);
		scene->addChild(ticker);
	}
}

void UIAdapter::addTickerToCurrentScene() {
	addLogicTick(cur_scene);
}

void UIAdapter::onOpponentChosen(string &opponent) {
	GameLogic::getInstance()->makeGameRequest(opponent);
}
