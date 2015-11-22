#include "GameLogic.h"
#include "LogInScene.h"

using namespace quoridor;

const ExitGames::Common::JString GameLogic::serverAddress = L"ns.exitgamescloud.com:" + ExitGames::Common::JString(ExitGames::Photon::NetworkPort::TCP);
const ExitGames::Common::JString GameLogic::appId = L"6061fe2f-6a86-49d9-9e76-856493cbd761";
const ExitGames::Common::JString GameLogic::version = L"1.0";

GameLogic *GameLogic::getInstance() {
	if (GameLogic::instance == nullptr) {
		GameLogic::instance = new GameLogic();
		GameLogic::instance->ui_adapter = new UIAdapter();
	}
	return GameLogic::instance;
}

void GameLogic::startGame() {
	//initializing NetworkListener
	this->ui_adapter->start();
}

void GameLogic::connect(std::string &username) {
	network_listener = new NetworkListener();
	network_listener->registerNetworkObserver(this);
	auto client = new ExitGames::LoadBalancing::Client(*network_listener, appId, version, ExitGames::Common::JString(username.c_str()));
	network_listener->setLBC(client);
	bool res = client->connect();
	ticker = new LogicTick(client);
	ticker->retain();
	ui_adapter->addTickerToCurrentScene();
	cocos2d::log("GRINLOG: GameLogic::connect returned %d", res ? 1 : 0);
}

void GameLogic::receiveMessage(NetworkMessage message) {
	cocos2d::log("GRINLOG:Message from observer received");
	switch (message.get_type()) {
		case NetworkMessage::MessageType::MESSAGE_COMMON_ROOM_CONNECTED:
			state = GameState::GAME_STATE_CONNECTED_TO_SERVER;
			auto all_players = network_listener->getAllPlayersInCurrentRoom();
			ui_adapter->renderChooseOpponentScene(all_players);
			break;
	}
}


GameLogic::~GameLogic() {
	delete this->ui_adapter;
	delete ticker;
	//delete this->network_listener;
}

UIAdapter* GameLogic::getUIAdapter() {
	return instance->ui_adapter;
}

LogicTick *GameLogic::getTicker() {
	return GameLogic::getInstance()->ticker;
}
