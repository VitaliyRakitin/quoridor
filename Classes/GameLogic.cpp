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
	ticker = new LogicTick(client);
	bool res = client->connect();
	cocos2d::log("GRINLOG: GameLogic::connect returned %d", res ? 1 : 0);
}

void GameLogic::receiveMessage() {
	cocos2d::log("GRINLOG:Message from observer received");
}


GameLogic::~GameLogic() {
	delete this->ui_adapter;
	delete ticker;
	//delete this->network_listener;
}

UIAdapter* GameLogic::getUIAdapter() {
	return instance->ui_adapter;
}
