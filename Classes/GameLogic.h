/*
 * GameLogic.h
 *
 *  Created on: Nov 17, 2015
 *      Author: grin3s
 */
#pragma once

#include "UIAdapter.h"
#include "cocos2d.h"
#include "Photon-cpp/inc/PhotonPeer.h"

namespace quoridor {
	class UIAdapter;
	class GameLogic {
	private:
		UIAdapter *ui_adapter = nullptr;
		static GameLogic *instance;
		GameLogic() = default;
	public:
		static const ExitGames::Common::JString serverAddress;
		static const ExitGames::Common::JString appId;
		GameLogic(const GameLogic&) = delete;
		GameLogic& operator=(const GameLogic&) = delete;
		static GameLogic *getInstance();
		void startGame();
		~GameLogic();
	};
}

