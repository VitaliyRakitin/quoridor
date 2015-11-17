#include "GameLogic.h"

using namespace quoridor;

const ExitGames::Common::JString GameLogic::serverAddress = L"ns.exitgamescloud.com:" + ExitGames::Common::JString(ExitGames::Photon::NetworkPort::TCP);
const ExitGames::Common::JString GameLogic::appId = L"6061fe2f-6a86-49d9-9e76-856493cbd761";

GameLogic *GameLogic::getInstance() {
	if (GameLogic::instance == nullptr) {
		GameLogic::instance = new GameLogic();
		GameLogic::instance->ui_adapter = new UIAdapter(GameLogic::instance);
	}
	return GameLogic::instance;
}

void GameLogic::startGame() {
	this->ui_adapter->renderLogInScence();
}

GameLogic::~GameLogic() {
	delete this->ui_adapter;
}
