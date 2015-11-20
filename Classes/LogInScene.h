/*
 * LogInScene.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin
 */

#pragma once

#include "cocos2d.h"
#include "UIAdapter.h"

namespace quoridor {
	class LogInScene: public cocos2d::Scene {
	private:
		LogInScene(){};
	public:
		static LogInScene* createScene();
		CREATE_FUNC(LogInScene);
	};
}

