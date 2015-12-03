#include "GameData.h"

using namespace quoridor;

Move::Move(MoveType in_type, std::tuple<int, int> in_pos, std::string &in_player_id, WallOrientation in_wall_orientation):
		type(in_type),
		pos(in_pos),
		player_id(in_player_id),
		wall_orientation(in_wall_orientation)
{

}

PawnPosition::PawnPosition(std::tuple<int, int>& data) {
	x = std::get<0>(data);
	y = std::get<0>(data);
}
