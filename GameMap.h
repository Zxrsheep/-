#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include<iostream>
#include "time.h"
# include "stdlib.h"
#include "SpriteBase.h"
#include "math.h"
#include"chooseweapon.h"
#include"EndScene.h"
#include"VctoryScene.h"

extern int weapon;

USING_NS_CC;
#define monsterrange 100
using namespace std;
using namespace CocosDenshion;
using namespace ui;

class GameMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool animating = false;
	bool ismove = false;
	bool rightposition(cocos2d::Vec2 position);
	virtual bool init();
	cocos2d::TMXTiledMap* tilemap;
	cocos2d::TMXLayer* collidable;
	cocos2d::Sprite* arrow;
	cocos2d::Sprite* hammer;
	cocos2d::Sprite* monsterarrow;
	cocos2d::Sprite* arrowman;
	cocos2d::Sprite* monster;
	cocos2d::Sprite* HP;
	cocos2d::Sprite* EXP;
	LoadingBar* Loadingbar;
	LoadingBar* LoadingbarEXP;
	LoadingBar* Loadingbarman;
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	int _count;
	cocos2d::Vector<Sprite*> _HPArray;
	cocos2d::Vector<Sprite*> _EXPArray;
	//cocos2d::Animate* getAnimateByName(cocos2d::EventKeyboard::KeyCode key);
	int offsetX = 0;
	int offsetY = 100;
	//void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void animationcreate(int direct);
	void monsteranimationcreate(int direct);
	void backmenu(cocos2d::Ref* pSender);
	void OnAction(cocos2d::Ref* pSender);
	// a selector callback
	// implement the "static create()" method manually
	void keyupdate(float delta) ;//override
	bool keyState(cocos2d::EventKeyboard::KeyCode key);
	void move(cocos2d::EventKeyboard::KeyCode Code);
	CREATE_FUNC(GameMap);


	//人物怪物信息，shengming,血条
	float attposx;
	float attposy;
	float range1 = 180.0;
	float range2 = 130;
	int num = 3;
	int _moveCount = 0;
	float manlife =100;
	float currentmanlife=100;
	float manpercent = 100*(float)(currentmanlife / manlife);
	float monsterlife = 100;
	float currentmonsterlife = 100;
	float monsterpercent = 100 * (float)(currentmonsterlife / monsterlife);
	float expmax = 100;
	float currentexp = 0;
	float exppercent = 100 * (float)(currentexp / expmax);
	int level = 0;
	int dir = 1;
	int monsterCount = 0;
	cocos2d::Vec2 randomPosition();//怪物出现坐标，移动坐标。
	cocos2d::Vec2 randomMovePosition(cocos2d::Sprite* monster);
	void updateHPSprite(float delta);
	void updateEXPSprite(float delta);
	void levelup(float delta);
	void pickup(float delta);
	void updateMonsterSprite(float delta);

	void slowupdate(float delta);
	void monsterrandommove();
	void monstermoveto(int direction);
	float angle(cocos2d::Vec2 beginpos, cocos2d::Vec2 endpos);
	cocos2d::Vec2 attackpos(cocos2d::Vec2 beginpos, cocos2d::Vec2 endpos, float range);
	void CallFunremove();
	void CallFunremovemon();

	//攻击
	bool isshoot=false;
	bool monisshot = false;
	int screenwidth, screenheight;
	void scheduleUpdate(float delta);
	void playeraction();
    void monsterattack();
	void monsteraction();
	void attackman();
	void shootaction();
	void monstershoot();
	void quickupdate(float  delta);
	//碰撞
	bool isCollidearrow();
	bool monisCollidearrow();
	void collisionDetection();
	void aishootcollisionDetection(float delta);

	//武器
	void waeponjudge();
	int selectedweapon = ChooseWeapon::weapon;




private:
	Label* Level_;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};



#endif  __HELLOWORLD_SCENE_H__


