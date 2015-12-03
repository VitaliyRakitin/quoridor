#pragma once
#include <string>
#include <vector>
#include "BasePlayer.h"
#include "GameData.h"

namespace quoridor {

typedef enum {
	LOCAL_VS_LOCAL_2,
	LOCAL_VS_NETWORK_2
} MatchType;

class Match {
	MatchType type;
	int turn;
	std::vector<BasePlayer*> player_list;
	Position pos;
	static bool checkMove(Move &move);
	void updatePosition(Move &move);
public:
	Match(MatchType in_type, std::vector<std::string> &players);
	void onLocalMove(Move move, bool check);
};
}
