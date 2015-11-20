#pragma once
#include <string>
#include "cocos2d.h"
#include <thread>
#include <functional>
#include <chrono>

#define LOGIC_TICK_INTERVAL 30

USING_NS_CC;

class LogicTick {
private:
	std::thread task_thread;
public:
	LogicTick(ExitGames::LoadBalancing::Client* lbc):
		mLbc(lbc)
	{
		task_thread = std::thread([=](){
			while (true) {
				LogicTick::tick();
				std::this_thread::sleep_for(std::chrono::milliseconds(LOGIC_TICK_INTERVAL));
			}
		});
		task_thread.detach();
	}
	void tick() {
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
