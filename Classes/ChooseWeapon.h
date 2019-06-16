#ifndef __CHOOSE_WEAPON_H__
#define __CHOOSE_WEAPON_H__

#include"cocos2d.h"
#include "iostream"
#include "GameMap.h"
using namespace std;


//extern int weapon;

class ChooseWeapon :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	static int weapon;
	void Weapon_1(Ref* pSender);
	void Weapon_2(Ref* pSender);
//	void enterGame(Ref* pSender);
	void backmainmenu(cocos2d::Ref* pSender);
	CREATE_FUNC(ChooseWeapon);
};

#endif __CHOOSE_WEAPON_H__
