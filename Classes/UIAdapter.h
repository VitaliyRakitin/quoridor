/*
 * UIAdapter.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin
 */
#pragma once

#include "GameLogic.h"
#include "cocos2d.h"

namespace quoridor {
	class GameLogic;
	class UIAdapter {
	private:
		cocos2d::Scene *cur_scene = nullptr;
		GameLogic *game_logic = nullptr;
	public:
		UIAdapter(GameLogic *g_l):game_logic(g_l){};
		void renderLogInScence();
	};
}

