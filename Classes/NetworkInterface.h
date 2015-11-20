#pragma once
#include <string>
#include "cocos2d.h"

#define LOGIC_TICK_INTERVAL 0.01f

USING_NS_CC;

class LogicTick : public CCNode {
public:
	LogicTick(ExitGames::LoadBalancing::Client* lbc):
		mLbc(lbc)
	{
		schedule(schedule_selector(LogicTick::tick), LOGIC_TICK_INTERVAL);
	}
	void tick(float) {
		cocos2d::log("GRINLOG: tick");
		mLbc->service();
	}

private:
	ExitGames::LoadBalancing::Client* mLbc;
};

class NetworkMessage {
private:
	std::string text;
public:
	std::string get_text() {
		return text;
	}
};


class NetworkObserver {
public:
	virtual void receiveMessage() = 0;
	virtual ~NetworkObserver(){};
};
