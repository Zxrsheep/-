#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class GameMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	// implement the "static create()" method manually
	CREATE_FUNC(GameMap);
};

#endif  __HELLOWORLD_SCENE_H__


