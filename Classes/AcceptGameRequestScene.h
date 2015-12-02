#pragma once

#include "cocos2d.h"
#include <string>

namespace quoridor {
	class AcceptGameRequestScene: public cocos2d::Scene {
	private:
		AcceptGameRequestScene(){};
	public:
		static AcceptGameRequestScene* createScene(std::string &opponent);
		CREATE_FUNC(AcceptGameRequestScene);
	};
}
