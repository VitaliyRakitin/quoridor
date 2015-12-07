#include "PlayWithBot.h"
#include "UIAdapter.h"
#include "GameLogic.h"
#include <vector>
#include <string>
#include <time.h>

using namespace cocos2d;
using namespace quoridor;
using namespace std;

struct tbrick {
	int x;
	int y;
	bool reverse; // 0 - if horizontal
	Sprite* sprite;
};
int was_touch_block = -1;
cocos2d::Vec2 were_touch,save_pos;
clock_t start_time;

tbrick bricks[20];

PlayWithBot::PlayWithBot() {}
PlayWithBot::~PlayWithBot() {}

void change_rotate(int i) {
	cocos2d::log("I rotate block %d\n",i);
	Vec2 pos = bricks[i].sprite->getPosition();
	float Scale = bricks[i].sprite->getScale();
	bricks[i].sprite->removeFromParentAndCleanup(true);
	if (bricks[i].reverse) {
		bricks[i].reverse = 0;
		bricks[i].sprite = Sprite::create("brick.png");
	} else {
		bricks[i].reverse = 1;
		bricks[i].sprite = Sprite::create("brickRev.png");
	}
	bricks[i].sprite->setScale(Scale);
	bricks[i].sprite->setPosition(pos);
}

cocos2d::Vec2 PlayWithBot::FindIJfield(cocos2d::Vec2 p, cocos2d::Rect rect)
{
	cocos2d::Vec2 answ;
	float start_x = rect.getMinX();
	float start_y = rect.getMinY();
	float next = (-(start_x) + (rect.getMaxX())) / 9;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (start_x + i*next <= p.x && p.x <= start_x + (i + 1)*next) {
				if (start_y + j*next <= p.y && p.y <= start_y + (j + 1)*next) {
					cocos2d::log("Was touched field %d %d \n",i,j);
					answ.x = i;
					answ.y = j;
					return answ;
				}
			}
		}
	}
	answ.x = -1;
	answ.y = -1;
	return answ;
}

cocos2d::Vec2 PlayWithBot::FindIJBlock(cocos2d::Vec2 p, cocos2d::Rect rect, int i, bool Image)
{
	cocos2d::Vec2 answ;
	float start_x = rect.getMinX();
	float start_y = rect.getMinY();
	float next = (-(start_x) + (rect.getMaxX())) / 9;
	start_x += next;
	start_y += next;
	float eps = min(bricks[i].sprite->getContentSize().height,bricks[i].sprite->getContentSize().width);
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			float length = sqrt((start_x + i*next - p.x)*(start_x + i*next - p.x) + (start_y + j*next - p.y)*(start_y + j*next - p.y));
			if (length < 5*eps) {
				answ.x = i;
				answ.y = j;
				if (!Image)
					bricks[was_touch_block].sprite->setPosition(start_x + i*next,start_y + j*next);
				else {
					bricks[18 + bricks[was_touch_block].reverse].sprite->setVisible(true);
					bricks[18 + bricks[was_touch_block].reverse].sprite->setPosition(start_x + i*next,start_y + j*next);
				}
				return answ;
			}
		}
	}
	answ.x = -1;
	answ.y = -1;
	return answ;
}


bool PlayWithBot::inField(cocos2d::Vec2 p, cocos2d::Rect rect)
{
	if (rect.getMinX()<= p.x  && p.x <= rect.getMaxX()) {
		if (rect.getMinY() <= p.y && p.y <= rect.getMaxY()) {
			return true;
		}
	}
	return false;
}

int PlayWithBot::FindNumberBlock(cocos2d::Vec2 p)
{
	for (int i = 0; i < 18; ++i) {
		if (bricks[i].x != -1)
			continue;
		Vec2 brick_pos = bricks[i].sprite->getPosition();
		if (bricks[i].reverse == 0) {
			float eps = bricks[i].sprite->getContentSize().height;
			float weidht = bricks[i].sprite->getContentSize().width;
			if (brick_pos.x - weidht<= p.x and p.x <= brick_pos.x + weidht) {
				if (brick_pos.y - 7*eps <= p.y and p.y <= brick_pos.y + 7*eps) {
					were_touch.x = brick_pos.x - p.x;
					were_touch.y = brick_pos.y - p.y;
					return i;
				}
			}
		} else {
			float eps = bricks[i].sprite->getContentSize().width;
			float weidht = bricks[i].sprite->getContentSize().height;
			if (brick_pos.x - 7*eps<= p.x and p.x <= brick_pos.x + 7*eps) {
				if (brick_pos.y - weidht <= p.y and p.y <= brick_pos.y + weidht) {
					were_touch.x = brick_pos.x - p.x;
					were_touch.y = brick_pos.y - p.y;
					return i;
				}
			}
		}
	}
	return -1;
}

void PlayWithBot::onTouchMoved(Touch* touch, Event* event, Sprite* mySprite)
{
	cocos2d::log("I was in moved");
	if (was_touch_block != -1) {
		bricks[was_touch_block].sprite->setPosition(touch->getLocation().x + were_touch.x, touch->getLocation().y + were_touch.y);
		Vec2 tt = FindIJBlock(bricks[was_touch_block].sprite->getPosition(),mySprite->getBoundingBox(),was_touch_block,true);
		if (tt.x == -1) {
			bricks[18 + bricks[was_touch_block].reverse].sprite->setVisible(false);
		}
	}
}

PlayWithBot* PlayWithBot::createScene()
{
    auto scene = PlayWithBot::create();
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    auto ui_adapter = GameLogic::getUIAdapter();
    Sprite* mySprite = Sprite::create("desk.png");
    Sprite* player = Sprite::create("player.png");
    player->setAnchorPoint(Vec2(0, 0));
    player->setPosition(0, 0);
    mySprite->addChild(player);
    mySprite->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 25);
    mySprite->setScale((visibleSize.height / mySprite->getContentSize().height));
    player->setScale(mySprite->getContentSize().height / (9 * player->getContentSize().height));
    scene->addChild(mySprite);
    //here i start add bricks
	bricks[18].sprite = Sprite::create("brickImage.png");
	bricks[19].sprite = Sprite::create("brickRevImage.png");
	bricks[18].sprite->setScale(mySprite->getContentSize().width / (3.5 * bricks[18].sprite->getContentSize().width));
	bricks[19].sprite->setScale(mySprite->getContentSize().width / (3.5 * bricks[19].sprite->getContentSize().height));
	scene->addChild(bricks[18].sprite);
	scene->addChild(bricks[19].sprite);
	bricks[18].sprite->setVisible(false);
	bricks[19].sprite->setVisible(false);
    for (int i = 0; i < 2; ++i) {
    	for (int j = 0; j < 9; ++j) {
    		bricks[i*9 + j].sprite = Sprite::create("brick.png");
    		bricks[i*9 + j].x = -1;
    		bricks[i*9 + j].y = -1;
    		bricks[i*9 + j].reverse = 0;
    		bricks[i*9 + j].sprite->setScale(mySprite->getContentSize().width / (3.5 * bricks[i*9 + j].sprite->getContentSize().width));
    		float width = bricks[i*9 + j].sprite->getContentSize().width;
    		bricks[i*9 + j].sprite->setPosition(visibleSize.width - 1 - width / 2.0 - width * (i + i*0.2),visibleSize.height - j * width / 2 - 15*i);
    		scene->addChild(bricks[i*9 + j].sprite);
    	}
    }
    //here i stop add bricks
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = [=](Touch *touch, Event *unused_event) -> bool {
    	Vec2 touch_loc = touch->getLocation();
    	Vec2 tt = FindIJfield(touch_loc,mySprite->getBoundingBox());
    	if (tt.x != -1 && tt.y != -1) {
    		 float cur = player->getContentSize().height;
    		 auto actionMove = MoveTo::create(1, Vec2(cur*tt.x, cur*tt.y));
    		 player->runAction(actionMove);
    	} else {
    		was_touch_block  = FindNumberBlock(touch_loc);
    		save_pos = bricks[was_touch_block].sprite->getPosition();
    		start_time = clock();
    	}
    	return true;
    };
    eventListener->onTouchMoved = CC_CALLBACK_2(PlayWithBot::onTouchMoved, scene, mySprite);
    eventListener->onTouchEnded = [=](Touch *touch, Event *unused_event) -> bool {
    	Vec2 touch_loc = touch->getLocation();
        if (was_touch_block != -1) {
        	if ((double)(clock() - start_time)/CLOCKS_PER_SEC < 0.15) {
        		cocos2d::log("It was reverse!");
        		change_rotate(was_touch_block);
        		scene->addChild(bricks[was_touch_block].sprite);
        		return true;
        	}
        	Vec2 tt = FindIJBlock(bricks[was_touch_block].sprite->getPosition(),mySprite->getBoundingBox(),was_touch_block,false);
        	if (tt.x != -1) {

        		//bricks[was_touch_block].sprite->setPosition();
        	} else {
        		if (inField(touch_loc,mySprite->getBoundingBox())) {
        			bricks[was_touch_block].sprite->setPosition(save_pos);
        		}
        	}
        	bricks[18 + bricks[was_touch_block].reverse].sprite->setVisible(false);
        	was_touch_block = -1;
        }
        cocos2d::log("good end touch");
       	return true;
    };
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, mySprite);

    MenuItemFont::setFontName("Marker Felt.ttf");
    Vector<MenuItem*> items;
    auto menu = Menu::createWithArray(items);
    menu->alignItemsVertically();
    scene->addChild(menu);

    return scene;
}

Field::Field() {}
Field::~Field() {}
Field* Field::create()
{
	Field* result = (Field*)Sprite::create("field.png");
	result->addEvents();
	return result;
}

void Field::initOptions(float x, float y)
{
	this->setPosition(x,y);
	this->setScale(3);
    // do things here like setTag(), setPosition(), any custom logic.
}

void Field::addEvents()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
    	cocos2d::log("Was touch");
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Rect rect = this->getBoundingBox();
        cocos2d::log("Our pos - %f %f",p.x,p.y);
        cocos2d::log("Box pos - %f %f %f %f",rect.getMinX(),rect.getMinY(),rect.getMaxX(),rect.getMaxY());
        if(rect.containsPoint(p))
        {
        	cocos2d::log("Was true touch!");
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
    	Field::touchEvent(touch,0);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Field::touchEvent(cocos2d::Touch* touch, cocos2d::Vec2 _p)
{
	cocos2d::log("dsdss");
}
