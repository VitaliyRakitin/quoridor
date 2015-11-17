#include "UIAdapter.h"
#include "LogInScene.h"

USING_NS_CC;

using namespace quoridor;

void UIAdapter::renderLogInScence() {
	auto director = cocos2d::Director::getInstance();
	cur_scene = LogInScene::createScene();
	director->runWithScene(cur_scene);
}
