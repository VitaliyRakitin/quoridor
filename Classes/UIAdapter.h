/*
 * UIAdapter.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin
 */
#pragma once

#include "cocos2d.h"
#include <string>

namespace quoridor {
	class UIAdapter {
	private:
		cocos2d::CCScene* rootScene = nullptr;
	public:
		void setRootScene(cocos2d::CCScene* in_scene);
		cocos2d::CCScene* getRootScene();
		void logIn(std::string &username);
		UIAdapter();
		void renderLogInScence();
	};
}

