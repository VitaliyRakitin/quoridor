#pragma once

#include "cocos2d.h"

namespace quoridor {
	class StartScene: public cocos2d::Scene {
	private:
		StartScene(){};
	public:
		static StartScene* createScene();
		CREATE_FUNC(StartScene);
	};
}
