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
	public:
		typedef enum {
			GAME_STATE_INACTIVE,
			GAME_STATE_CONNECTED_TO_SERVER,
			GAME_STATE_SENDING_GAME_REQUEST,
			GAME_STATE_PLAYING
		} GameState;
	private:
		GameState state = GAME_STATE_INACTIVE;
		LogicTick *ticker = nullptr;
		UIAdapter *ui_adapter = nullptr;
		static GameLogic *instance;
		NetworkListener *network_listener = nullptr;
		GameLogic() = default;
		std::string local_player_name;
	public:
		//from NetworkObserver
		virtual void receiveMessage(NetworkMessage message);
		static const ExitGames::Common::JString serverAddress;
		static const ExitGames::Common::JString appId;
		static const ExitGames::Common::JString version;
		GameLogic(const GameLogic&) = delete;
		GameLogic& operator=(const GameLogic&) = delete;
		static GameLogic *getInstance();
		static UIAdapter* getUIAdapter();
		void startGame();
		void connect(std::string &username);
		static LogicTick *getTicker();
		~GameLogic();
	};
}

