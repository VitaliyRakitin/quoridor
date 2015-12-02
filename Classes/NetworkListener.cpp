/*
 * NetworkListener.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: grin
 */
#include "NetworkListener.h"
#include <iostream>
#include <thread>
#include <functional>
using namespace ExitGames;

ExitGames::Common::JString NetworkListener::commonRoom = "Common Room";

NetworkListener::NetworkListener(): mLbc(NULL) {}
NetworkListener::~NetworkListener() {}
void NetworkListener::setLBC(ExitGames::LoadBalancing::Client* pLbc) {
	this->mLbc = pLbc;
}
bool NetworkListener::connect(void) {
	return this->mLbc->connect();
}

void NetworkListener::service(void) {
	cocos2d::log("GRINSERV:NetworkListener service");
}
// receive and print out debug out here
void NetworkListener::debugReturn(int debugLevel, const Common::JString& string){cocos2d::log("GRINLOG:debugReturn");}

// implement your error-handling here
void NetworkListener::connectionErrorReturn(int errorCode){cocos2d::log("GRINLOG:connectionErrorReturn: %d\n", errorCode);}
void NetworkListener::clientErrorReturn(int errorCode){cocos2d::log("GRINLOG:clientErrorReturn %d\n", errorCode);}
void NetworkListener::warningReturn(int warningCode){cocos2d::log("GRINLOG:warningReturn %d\n", warningCode);}
void NetworkListener::serverErrorReturn(int errorCode){cocos2d::log("GRINLOG:serverErrorReturn %d\n", errorCode);}

// events, triggered by certain operations of all players in the same room
void NetworkListener::joinRoomEventAction(int playerNr, const Common::JVector<int>& playernrs, const Player& player){
	cocos2d::log("GRINLOG:joinRoomEventAction\n");
	auto cur_room_name = mLbc->getCurrentlyJoinedRoom().getName();
	if (cur_room_name == NetworkListener::commonRoom) {
		NetworkMessage m = NetworkMessage(NetworkMessage::MessageType::MESSAGE_COMMON_ROOM_CONNECTED);
		notifyAllObservers(&m);
	}
	cocos2d::log("GRINLOG:joinRoomEventAction finished\n");
}
void NetworkListener::leaveRoomEventAction(int playerNr, bool isInactive){cocos2d::log("GRINLOG:leaveRoomEventAction\n");}

void NetworkListener::customEventAction(int playerNr, nByte eventCode, const Common::Object& eventContent){
	cocos2d::log("GRINLOG:customEventAction: %d\n", eventCode);
	switch (eventCode) {
	case NetworkMessage::MESSAGE_GAME_REQUEST:
	{
		GameRequestMessage::DictType data = ExitGames::Common::ValueObject<GameRequestMessage::DictType>(eventContent).getDataCopy();
		GameRequestMessage m = GameRequestMessage(data);
		notifyAllObservers(&m);
		break;
	}
	case NetworkMessage::MESSAGE_GAME_REQUEST_ANSWER:
	{
		GameRequestAnswerMessage::HashType data = ExitGames::Common::ValueObject<GameRequestAnswerMessage::HashType>(eventContent).getDataCopy();
		auto m = GameRequestAnswerMessage(data);
		notifyAllObservers(&m);
		break;
	}
	}
}

// callbacks for operations on server
void NetworkListener::connectReturn(int errorCode, const Common::JString& errorString){
	bool roomExists = false;
	cocos2d::log("GRINLOG:connectReturn: %d\n", errorCode);
	if (errorCode == ExitGames::LoadBalancing::ErrorCode::OK) {
		//we connected
	}
}

void NetworkListener::disconnectReturn(void){cocos2d::log("GRINLOG:disconnectReturn\n");}
void NetworkListener::createRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:createRoomReturn\n");}

void NetworkListener::joinRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){

	cocos2d::log("GRINLOG:joinRoomReturn\n");

}

void NetworkListener::joinRandomRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:joinRandomRoomReturn\n");}
void NetworkListener::leaveRoomReturn(int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:leaveRoomReturn\n");}
void NetworkListener::joinLobbyReturn(void){cocos2d::log("GRINLOG:joinLobbyReturn\n");}
void NetworkListener::leaveLobbyReturn(void){cocos2d::log("GRINLOG:leaveLobbyReturn\n");}
void NetworkListener::onFindFriendsResponse(void) {cocos2d::log("GRINLOG:onFindFriendsResponse\n");}
void NetworkListener::onLobbyStatsResponse(const Common::JVector<LobbyStatsResponse>& lobbyStats) {cocos2d::log("GRINLOG:onLobbyStatsResponse\n");}
void NetworkListener::webRpcReturn(int errorCode, const Common::JString& errorString, const Common::JString& uriPath, int resultCode, const Common::Dictionary<Common::Object, Common::Object>& returnData) {cocos2d::log("GRINLOG:webRpcReturn\n");}

// info, that certain values have been updated
void NetworkListener::onRoomListUpdate(void) {
	cocos2d::log("GRINLOG:onRoomListUpdate\n");
	auto roomNames = mLbc->getRoomNameList();
	if (roomNames.getIsEmpty()) {
		bool res = mLbc->opCreateRoom(NetworkListener::commonRoom, true, true, COMMON_ROOM_SIZE);
		cocos2d::log("GRINLOG:opCreatedRoom: %d\n", res ? 1 : 0);
	}
	else {
		bool res = mLbc->opJoinRoom(NetworkListener::commonRoom);
		cocos2d::log("GRINLOG:opJoinedRoom: %d\n", res ? 1 : 0);
	}
}
void NetworkListener::onRoomPropertiesChange(const Common::Hashtable& changes) {cocos2d::log("GRINLOG:onRoomPropertiesChange\n");}
void NetworkListener::onPlayerPropertiesChange(int playerNr, const Common::Hashtable& changes) {cocos2d::log("GRINLOG:onPlayerPropertiesChange\n");}
void NetworkListener::onAppStatsUpdate(void) {cocos2d::log("GRINLOG:onAppStatsUpdate\n");}
void NetworkListener::onLobbyStatsUpdate(const Common::JVector<LobbyStatsResponse>& lobbyStats) {cocos2d::log("GRINLOG:onLobbyStatsUpdate\n");}
void NetworkListener::onCacheSliceChanged(int cacheSliceIndex) {cocos2d::log("GRINLOG:onCacheSliceChanged\n");}

// custom authentication
void NetworkListener::onCustomAuthenticationIntermediateStep(const Common::Dictionary<Common::JString, Common::Object>& customResponseData){cocos2d::log("GRINLOG:onCustomAuthenticationIntermediateStep\n");}

// receive available server regions during connect workflow (if you have specified in the constructor, not to use the default region)
void NetworkListener::onAvailableRegions(const Common::JVector<Common::JString>& availableRegions, const Common::JVector<Common::JString>& availableRegionServers){cocos2d::log("GRINLOG:onAvailableRegions\n");}

void NetworkListener::onSecretReceival(const Common::JString& secret){cocos2d::log("GRINLOG:onSecretReceival\n");}

void NetworkListener::registerNetworkObserver(NetworkObserver *observer) {
	observers.push_back(observer);
}

vector<string>& NetworkListener::getAllPlayersInCurrentRoom() {
	current_room_players.clear();
	auto room = mLbc->getCurrentlyJoinedRoom();
	auto n_players = room.getPlayerCount();
	cocos2d::log("GRINLOG:NetworkListener::getAllPlayersInCurrentRoom, n_players = %d", n_players);
	auto all_players = room.getPlayers();
	auto local_player_name = getLocalPlayerName();
	for (int i = 0; i < n_players; i++) {
		auto player = all_players[i];
		auto name = player->getName().ANSIRepresentation().cstr();
		auto str_name = string(name);
		if (str_name != local_player_name) {
			current_room_players.push_back(str_name);
			current_room_players_numbers.push_back(player->getNumber());
		}
	}
	return current_room_players;
}

string NetworkListener::getLocalPlayerName() {
	return string(mLbc->getLocalPlayer().getName().ANSIRepresentation().cstr());
}

void NetworkListener::sendGameRequestToOpponent(string &opponent) {
	auto from = getLocalPlayerName();
	auto request = GameRequestMessage(from, opponent);
	auto recipient_number = getIntForPlayer(opponent);
	mLbc->opRaiseEvent(false, request.getDictionary(), request.get_type(), 0, 0, &recipient_number, 1);
}

int NetworkListener::getIntForPlayer(string &player) {
	for (auto i = 0; i < current_room_players.size(); i++) {
		if (player == current_room_players[i]) {
			return current_room_players_numbers[i];
		}
	}
	return -1;
}

void NetworkListener::notifyAllObservers(NetworkMessage *message) {
	for (auto iter = observers.begin(); iter < observers.end(); iter++) {
		(*iter)->receiveMessage(message);
	}
}

void NetworkListener::sendMessageToPlayerInCurrentRoom(GameRequestAnswerMessage& message, string &opponent_name) {
	auto recipient_number = getIntForPlayer(opponent_name);
	mLbc->opRaiseEvent(false, message.getData(), message.get_type(), 0, 0, &recipient_number, 1);
}
