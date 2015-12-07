#pragma once

#include "cocos2d.h"
#include <string>

namespace quoridor {
	class PlayWithBot: public cocos2d::Scene {
	public:
		PlayWithBot();
		~PlayWithBot();
		static PlayWithBot* createScene();
		CREATE_FUNC(PlayWithBot);
		static cocos2d::Vec2 FindIJfield(cocos2d::Vec2 touch, cocos2d::Rect rect);
		static cocos2d::Vec2 FindIJBlock(cocos2d::Vec2 touch, cocos2d::Rect rect, int i, bool Image);
		static int FindNumberBlock(cocos2d::Vec2 p);
		static bool inField(cocos2d::Vec2 p, cocos2d::Rect rect);
		void onTouchMoved(cocos2d::Touch*, cocos2d::Event*, cocos2d::Sprite*);
		//void addEvents();
		//bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	};

	class Field : public cocos2d::Sprite
	{
	    public:
			Field();
	        ~Field();
	        static Field* create();
	        void initOptions(float x, float y);
	        void addEvents();
	        void touchEvent(cocos2d::Touch* touch,cocos2d::Vec2 _p);

	    private:

	};
}

