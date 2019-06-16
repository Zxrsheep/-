#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class HelpScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuMusicstopCallback(cocos2d::Ref* pSender);
	void menuMusicresumeCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(HelpScene);
};
#endif __HELP_SCENE_H__
