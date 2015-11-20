#include "UIAdapter.h"
#include "LogInScene.h"
#include "GameLogic.h"
#include "StartScene.h"

USING_NS_CC;

using namespace quoridor;

UIAdapter::UIAdapter() {
}

void UIAdapter::logIn(std::string &username) {
	GameLogic::getInstance()->connect(username);
	cocos2d::log("GRINLOG: UIAdapter::logIn");
}

void UIAdapter::renderLogInScence() {
	auto director = cocos2d::Director::getInstance();
	auto cur_scene = LogInScene::createScene();
	director->runWithScene(cur_scene);
}

void UIAdapter::start() {
	auto cur_scene = StartScene::createScene();
	Director::getInstance()->runWithScene(cur_scene);
}

void UIAdapter::onNetworkGameChosen() {
	auto cur_scene = LogInScene::createScene();
	Director::getInstance()->replaceScene(cur_scene);
}

