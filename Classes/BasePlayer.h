#pragma once
#include <string>
#include "GameData.h"

namespace quoridor {
typedef enum {
	LOCAL_PLAYER,
	NETWORK_PLAYER
} PlayerType;

class BasePlayer {
	std::string player_id;
	virtual void onOpponentMoved(Move &move) = 0;
public:
	BasePlayer(std::string &in_player_id);
	std::string &getPlayerId();
	virtual ~BasePlayer(){}
};

class LocalPlayer: public BasePlayer {
public:
	LocalPlayer(std::string &in_player_id);
	virtual void onOpponentMoved(Move &move);
};

class NetworkPlayer: public BasePlayer {
public:
	NetworkPlayer(std::string &in_player_id);
	virtual void onOpponentMoved(Move &move);
};
}
