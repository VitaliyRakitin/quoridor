#pragma once
#include <string>
#include "cocos2d.h"
#include <thread>
#include <functional>
#include <chrono>

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
		MESSAGE_
	} MessageType;
private:
	MessageType type;
	std::string text;
public:
	NetworkMessage(MessageType in_type):type(in_type){}
	MessageType get_type() {return type;}
	std::string get_text() {
		return text;
	}
};


class NetworkObserver {
public:
	virtual void receiveMessage(NetworkMessage message) = 0;
	virtual ~NetworkObserver(){};
};
