#include "UIAdapter.h"
#include "LogInScene.h"
#include "GameLogic.h"

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
	rootScene->addChild(cur_scene);
	director->replaceScene(cur_scene);
}

void UIAdapter::setRootScene(cocos2d::CCScene* in_scene) {
	rootScene = in_scene;
}

cocos2d::CCScene* UIAdapter::getRootScene() {
	return rootScene;
}
