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
#include "NetworkListener.h"
#include <string>
#include "NetworkInterface.h"

USING_NS_CC;

namespace quoridor {
	class GameLogic: NetworkObserver {
	private:
		LogicTick *ticker = nullptr;
		UIAdapter *ui_adapter = nullptr;
		static GameLogic *instance;
		NetworkListener *network_listener = nullptr;
		GameLogic() = default;
	public:
		//from NetworkObserver
		virtual void receiveMessage();
		static const ExitGames::Common::JString serverAddress;
		static const ExitGames::Common::JString appId;
		static const ExitGames::Common::JString version;
		GameLogic(const GameLogic&) = delete;
		GameLogic& operator=(const GameLogic&) = delete;
		static GameLogic *getInstance();
		static UIAdapter* getUIAdapter();
		void startGame();
		void connect(std::string &username);
		~GameLogic();
	};
}

