#pragma once

#include "cocos2d.h"
#include <vector>
#include <string>

using namespace std;

namespace quoridor {
	class ChooseOpponentScene: public cocos2d::Scene {
	private:
		ChooseOpponentScene(){};
	public:
		static ChooseOpponentScene* createScene(vector<string>& all_players);
		CREATE_FUNC(ChooseOpponentScene);
	};
}

