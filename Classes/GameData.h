#pragma once
#include <tuple>
#include <vector>

namespace quoridor {
typedef enum {
	VERTICAL,
	HORIZONTAL
} WallOrientation;

struct WallPosition {
	int x;
	int y;
	WallOrientation orientaion;
};

struct PawnPosition {
	int x;
	int y;

	PawnPosition(std::tuple<int, int>&);
};

struct Move {
	typedef enum {
		MOVE_PAWN,
		PLACE_WALL
	} MoveType;

	MoveType type;
	std::tuple<int, int> pos;
	std::string player_id;
	WallOrientation wall_orientation;

	Move(MoveType in_type, std::tuple<int, int> in_pos, std::string &in_player_id, WallOrientation in_wall_orientation);
};

class Position {
public:
	std::vector<WallPosition> wall_positions;
	std::vector<PawnPosition> pawn_positions;
	std::vector<int> n_walls_left;
};
}
