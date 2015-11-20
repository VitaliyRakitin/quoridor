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
	public:
		void logIn(std::string &username);
		UIAdapter();
		void renderLogInScence();
		void onNetworkGameChosen();
		void start();
	};
}

