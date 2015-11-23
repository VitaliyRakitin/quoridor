#pragma once
#include <string>
#include "cocos2d.h"
#include <thread>
#include <functional>
#include <chrono>
//#include "Common-cpp/inc/Dictionary.h"
#include "LoadBalancing-cpp/inc/Client.h"

#define LOGIC_TICK_INTERVAL 0.01f

USING_NS_CC;

class LogicTick: public cocos2d::CCNode {
public:
	LogicTick(ExitGames::LoadBalancing::Client* lbc):
		mLbc(lbc)
	{
		schedule(schedule_selector(LogicTick::tick), LOGIC_TICK_INTERVAL);
	}
	void tick(float) {
		mLbc->service();
	}

private:
	ExitGames::LoadBalancing::Client* mLbc;
};

class NetworkMessage {
public:
	typedef enum {
		MESSAGE_COMMON_ROOM_CONNECTED,
		MESSAGE_GAME_REQUEST
	} MessageType;
protected:
	MessageType type;
public:
	NetworkMessage(MessageType in_type):type(in_type){}
	MessageType get_type();
};

class GameRequestMessage: public NetworkMessage {
private:
	typedef ExitGames::Common::JString keyType;
	typedef ExitGames::Common::JString valueType;
	typedef ExitGames::Common::Dictionary<keyType, valueType> DictType;
	DictType m_dictionary;
public:
	GameRequestMessage(std::string &from, std::string &to);
	DictType& getDictionary();
};


class NetworkObserver {
public:
	virtual void receiveMessage(NetworkMessage message) = 0;
	virtual ~NetworkObserver(){};
};
