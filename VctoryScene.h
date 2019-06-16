#ifndef __VCTORY_SCENE_H__
#define __VCTORY_SCENE_H__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class VctoryScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	//void menuCloseCallback();
	//void menuAgainCallback(cocos2d::Ref* pSender);
	void again(cocos2d::Ref* pSender);
	void end(cocos2d::Ref* pSender);
	cocos2d::TMXTiledMap* tilemap;
	//void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool init();
	//void EndScene::GameMap(Ref* pSender);
	CREATE_FUNC(VctoryScene);

	//void EnterSecondScene(Ref *pSender);	//创建一个菜单回调函数，这里实现了场景的跳转
};
#endif __VCTORY_SCENE_H__
