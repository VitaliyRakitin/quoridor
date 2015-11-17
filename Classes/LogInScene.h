/*
 * LogInScene.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin
 */

#pragma once

#include "cocos2d.h"

namespace quoridor {
	class LogInScene: public cocos2d::Scene {
	public:
		static LogInScene* createScene();
		CREATE_FUNC(LogInScene);
	};
}

