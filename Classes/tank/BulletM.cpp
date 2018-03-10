#include "BulletM.h"

BulletM::BulletM()
{
}

BulletM::~BulletM()
{
}

bool BulletM::init()
{
	bool bRet = false;
	do
	{

		bRet = true;
	} while (false);
	return bRet;
}

int BulletM::getBulletNum(void* owner)
{
	auto num = 0;
	auto bullets = this->getChildren();
	for (auto i = 0; i < bullets.size(); i++)
	{
		auto bullet = (Bullet*)bullets.at(i);
		if (bullet->getOwner() == owner)
		{
			num++;
		}
	}
	return num;
}

void BulletM::createBullet(void* owner, float speed, int power, Vec2 pos, Direction direction,int distance)
{
	auto bullet = Bullet::create(owner, speed, power, pos, direction,distance);
	this->addChild(bullet);
}

void BulletM::pauseGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->pause();
	}
}

void BulletM::resumeGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->resume();
	}
}