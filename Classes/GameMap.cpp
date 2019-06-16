#include"GameMap.h"

USING_NS_CC;

Scene* GameMap::createScene()
{
	return GameMap::create();
}
bool GameMap::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;

}