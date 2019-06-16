#ifndef __RESULT_H__
#define __RESULT_H__
#include "cocos2d.h"

class result : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(result);
};
#endif __RESULT_H__
