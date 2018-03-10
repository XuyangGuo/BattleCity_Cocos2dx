#include "BulletM.h"

/*该类为子弹管理类，主要的函数是提供一个创建子弹的接口，并统计子弹的数目*/
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
//得到子弹数目
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
//创建子弹的接口
void BulletM::createBullet(void* owner, float speed, int power, Vec2 pos, Direction direction,int distance)
{
	auto bullet = Bullet::create(owner, speed, power, pos, direction,distance);
	this->addChild(bullet);
}
//暂停游戏的接口
void BulletM::pauseGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->pause();
	}
}
//重新开始游戏的接口
void BulletM::resumeGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->resume();
	}
}