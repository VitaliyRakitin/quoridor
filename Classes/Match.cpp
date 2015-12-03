#include "Match.h"
#include "cocos2d.h"

using namespace quoridor;

Match::Match(MatchType in_type, std::vector<std::string> &players):turn(0) {
	type = in_type;
	switch (type) {
	case LOCAL_VS_LOCAL_2:
		for (auto iter = players.begin(); iter < players.end(); iter++) {
			auto player = new LocalPlayer(*iter);
			player_list.push_back(player);
		}
		break;
	case LOCAL_VS_NETWORK_2:
		player_list.push_back(new LocalPlayer(players[0]));
		player_list.push_back(new NetworkPlayer(players[1]));
		break;
	default:
		break;
	}
}

void Match::update(Move &move) {
	switch (move.type) {
	case Move::MoveType::MOVE_PAWN:
		pos.pawn_positions[turn] = PawnPosition(move.pos);
		break;
	case Move::MoveType::PLACE_WALL:
		break;
	}
}

bool checkMove(Move &move) {
	return true;
}

void Match::onLocalMove(Move move, bool check) {
	cocos2d::log("GRINLOG: player %s moved", move.player_id.c_str());
	if (checkMove(move)) {
		updatePosition(move);
	}
}
