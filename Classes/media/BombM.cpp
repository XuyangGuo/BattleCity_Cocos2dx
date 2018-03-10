/***********************************************

该类用来管理爆炸动画，管理爆炸的生命周期

***********************************************/


#include "BombM.h"
#include "data/Global.h"
#include "scene/GameScene.h"

BombM::BombM()
{
}

BombM::~BombM()
{
}

void BombM::createBomb(BombType type, Vec2 pos)
{
	auto bomb = Bomb::create(type);
	bomb->setPosition(pos);
	this->addChild(bomb, 1);
}

void BombM::pauseGame()
{
	for (auto bomb : getChildren())
	{
		bomb->pause();
	}
}

void BombM::resumeGame()
{
	for (auto bomb : getChildren())
	{
		bomb->resume();
	}
}