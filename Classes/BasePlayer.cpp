#include "BasePlayer.h"

using namespace quoridor;

BasePlayer::BasePlayer(std::string &in_player_id):
	player_id(in_player_id)
{
}

std::string &BasePlayer::getPlayerId() {
	return player_id;
}

LocalPlayer::LocalPlayer(std::string &in_player_id):
	BasePlayer(in_player_id)
{
}

void LocalPlayer::onOpponentMoved(Move &move) {

}

NetworkPlayer::NetworkPlayer(std::string &in_player_id):
	BasePlayer(in_player_id)
{
}

void NetworkPlayer::onOpponentMoved(Move &move) {

}
