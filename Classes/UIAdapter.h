/*
 * UIAdapter.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin
 */
#pragma once

#include "cocos2d.h"
#include <string>
#include <vector>

using namespace std;

namespace quoridor {
	class UIAdapter {
	private:
		static void addLogicTick(cocos2d::Scene *scene);
		cocos2d::Scene *cur_scene;
	public:
		void logIn(std::string &username);
		UIAdapter();
		void renderLogInScence();
		void onNetworkGameChosen();
		void renderChooseOpponentScene(vector<string>& all_players);
		void start();
		void addTickerToCurrentScene();
		void onOpponentChosen(string &opponent);
	};
}

