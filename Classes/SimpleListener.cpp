/*
 * SimpleListener.cpp
 *
 *  Created on: Oct 19, 2015
 *      Author: grin
 */
#include "SimpleListener.h"
#include <iostream>
using namespace ExitGames;
SimpleListener::SimpleListener(): mLbc(NULL) {}
SimpleListener::~SimpleListener() {}
void SimpleListener::setLBC(ExitGames::LoadBalancing::Client* pLbc) {
	this->mLbc = pLbc;
}
bool SimpleListener::connect(void) {
	return this->mLbc->connect();
}

void SimpleListener::service(void) {
	cocos2d::log("GRINSERV:SimpleListener service");
}
// receive and print out debug out here
void SimpleListener::debugReturn(int debugLevel, const Common::JString& string){cocos2d::log("GRINLOG:debugReturn");}

// implement your error-handling here
void SimpleListener::connectionErrorReturn(int errorCode){cocos2d::log("GRINLOG:connectionErrorReturn: %d\n", errorCode);}
void SimpleListener::clientErrorReturn(int errorCode){cocos2d::log("GRINLOG:clientErrorReturn %d\n", errorCode);}
void SimpleListener::warningReturn(int warningCode){cocos2d::log("GRINLOG:warningReturn %d\n", warningCode);}
void SimpleListener::serverErrorReturn(int errorCode){cocos2d::log("GRINLOG:serverErrorReturn %d\n", errorCode);}

// events, triggered by certain operations of all players in the same room
void SimpleListener::joinRoomEventAction(int playerNr, const Common::JVector<int>& playernrs, const Player& player){cocos2d::log("GRINLOG:joinRoomEventAction\n");}
void SimpleListener::leaveRoomEventAction(int playerNr, bool isInactive){cocos2d::log("GRINLOG:leaveRoomEventAction\n");}

void SimpleListener::customEventAction(int playerNr, nByte eventCode, const Common::Object& eventContent){
	cocos2d::log("GRINLOG:customEventAction: %d\n", eventCode);
	if (eventCode == 300) {
		cocos2d::log("GRINLOG:event received\n");
	}
}

// callbacks for operations on server
void SimpleListener::connectReturn(int errorCode, const Common::JString& errorString){
	bool roomExists = false;
	cocos2d::log("GRINLOG:connectReturn: %d\n", errorCode);
	if (errorCode == ExitGames::LoadBalancing::ErrorCode::OK) {
		//we connected
	}
}

void SimpleListener::disconnectReturn(void){cocos2d::log("GRINLOG:disconnectReturn\n");}
void SimpleListener::createRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:createRoomReturn\n");}
void SimpleListener::joinRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:joinRoomReturn\n");}
void SimpleListener::joinRandomRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:joinRandomRoomReturn\n");}
void SimpleListener::leaveRoomReturn(int errorCode, const Common::JString& errorString){cocos2d::log("GRINLOG:leaveRoomReturn\n");}
void SimpleListener::joinLobbyReturn(void){cocos2d::log("GRINLOG:joinLobbyReturn\n");}
void SimpleListener::leaveLobbyReturn(void){cocos2d::log("GRINLOG:leaveLobbyReturn\n");}
void SimpleListener::onFindFriendsResponse(void) {cocos2d::log("GRINLOG:onFindFriendsResponse\n");}
void SimpleListener::onLobbyStatsResponse(const Common::JVector<LobbyStatsResponse>& lobbyStats) {cocos2d::log("GRINLOG:onLobbyStatsResponse\n");}
void SimpleListener::webRpcReturn(int errorCode, const Common::JString& errorString, const Common::JString& uriPath, int resultCode, const Common::Dictionary<Common::Object, Common::Object>& returnData) {cocos2d::log("GRINLOG:webRpcReturn\n");}

// info, that certain values have been updated
void SimpleListener::onRoomListUpdate(void) {
	cocos2d::log("GRINLOG:onRoomListUpdate\n");
	const ExitGames::Common::JString roomName = L"Room1";
	auto roomNames = mLbc->getRoomNameList();
	if (roomNames.getIsEmpty()) {
		bool res = mLbc->opCreateRoom(roomName, true, true, 4);
		cocos2d::log("GRINLOG:opCreatedRoom: %d\n", res ? 1 : 0);
	}
	else {
		bool res = mLbc->opJoinRoom(roomName);
		cocos2d::log("GRINLOG:opJoinedRoom: %d\n", res ? 1 : 0);
	}
}
void SimpleListener::onRoomPropertiesChange(const Common::Hashtable& changes) {cocos2d::log("GRINLOG:onRoomPropertiesChange\n");}
void SimpleListener::onPlayerPropertiesChange(int playerNr, const Common::Hashtable& changes) {cocos2d::log("GRINLOG:onPlayerPropertiesChange\n");}
void SimpleListener::onAppStatsUpdate(void) {cocos2d::log("GRINLOG:onAppStatsUpdate\n");}
void SimpleListener::onLobbyStatsUpdate(const Common::JVector<LobbyStatsResponse>& lobbyStats) {cocos2d::log("GRINLOG:onLobbyStatsUpdate\n");}
void SimpleListener::onCacheSliceChanged(int cacheSliceIndex) {cocos2d::log("GRINLOG:onCacheSliceChanged\n");}

// custom authentication
void SimpleListener::onCustomAuthenticationIntermediateStep(const Common::Dictionary<Common::JString, Common::Object>& customResponseData){cocos2d::log("GRINLOG:onCustomAuthenticationIntermediateStep\n");}

// receive available server regions during connect workflow (if you have specified in the constructor, not to use the default region)
void SimpleListener::onAvailableRegions(const Common::JVector<Common::JString>& availableRegions, const Common::JVector<Common::JString>& availableRegionServers){cocos2d::log("GRINLOG:onAvailableRegions\n");}

void SimpleListener::onSecretReceival(const Common::JString& secret){cocos2d::log("GRINLOG:onSecretReceival\n");}
