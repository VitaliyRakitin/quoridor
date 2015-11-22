/*
 * NetworkListener.h
 *
 *  Created on: Nov 18, 2015
 *      Author: grin
 */

#pragma once

#include "LoadBalancing-cpp/inc/Listener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "cocos2d.h"

#include "LoadBalancing-cpp/inc/Internal/PlayerFactory.h"
#include "LoadBalancing-cpp/inc/Internal/PlayerPropertiesCacher.h"
#include <vector>
#include <string>

#include "NetworkInterface.h"

#define COMMON_ROOM_SIZE 1024

using namespace ExitGames;
using namespace ExitGames::LoadBalancing;
using namespace std;

class NetworkListener: public ExitGames::LoadBalancing::Listener {
public:
	NetworkListener();
	~NetworkListener();
	void setLBC(ExitGames::LoadBalancing::Client* pLbc);
	bool connect(void);
	void service(void);
	ExitGames::LoadBalancing::Client* mLbc;
	void registerNetworkObserver(NetworkObserver *observer);
	vector<string>& getAllPlayersInCurrentRoom();
	string getLocalPlayerName();
private:
	vector<string> current_room_players;
	static ExitGames::Common::JString commonRoom;
	std::vector<NetworkObserver*> observers;
	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);

	virtual void customEventAction(int playerNr, nByte eventCode, const Common::Object& eventContent);

	// callbacks for operations on server
	virtual void connectReturn(int errorCode, const Common::JString& errorString);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const Common::Hashtable& roomProperties, const Common::Hashtable& playerProperties, int errorCode, const Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const Common::JString& errorString);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);
	virtual void onFindFriendsResponse(void);
	virtual void onLobbyStatsResponse(const Common::JVector<LobbyStatsResponse>& /*lobbyStats*/);
	virtual void webRpcReturn(int /*errorCode*/, const Common::JString& /*errorString*/, const Common::JString& /*uriPath*/, int /*resultCode*/, const Common::Dictionary<Common::Object, Common::Object>& /*returnData*/);

	// info, that certain values have been updated
	virtual void onRoomListUpdate(void);
	virtual void onRoomPropertiesChange(const Common::Hashtable& /*changes*/);
	virtual void onPlayerPropertiesChange(int /*playerNr*/, const Common::Hashtable& /*changes*/);
	virtual void onAppStatsUpdate(void);
	virtual void onLobbyStatsUpdate(const Common::JVector<LobbyStatsResponse>& /*lobbyStats*/);
	virtual void onCacheSliceChanged(int /*cacheSliceIndex*/);

	// custom authentication
	virtual void onCustomAuthenticationIntermediateStep(const Common::Dictionary<Common::JString, Common::Object>& /*customResponseData*/);

	// receive available server regions during connect workflow (if you have specified in the constructor, not to use the default region)
	virtual void onAvailableRegions(const Common::JVector<Common::JString>& /*availableRegions*/, const Common::JVector<Common::JString>& /*availableRegionServers*/);

	virtual void onSecretReceival(const Common::JString& /*secret*/);
};
