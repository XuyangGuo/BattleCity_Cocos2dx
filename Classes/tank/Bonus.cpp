#include "Bonus.h"
#include "data\Global.h"
#include "Scene\GameScene.h"
#include "media\AudioM.h"

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
}

Bonus* Bonus::create(BonusType type,Vec2 pos)
{
	Bonus *pRet = new Bonus();
	if (pRet && pRet->init(type,pos))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Bonus::init(BonusType type, Vec2 pos)
{
	bool bRet = false;
	do
	{
		_type = type;
		//this->initWithSpriteFrameName(String::createWithFormat("bonus_%d",(int)type)->getCString());
		this->initWithFile(String::createWithFormat("bonus_%d.png", (int)type)->getCString());

		int row, col;
		row = getRowNumberFromPosition(pos.y);
		col = getColNumberFromPosition(pos.x);
		this->setPosition(getPos(row, col).x - 16, getPos(row, col).y - 16);
		GameScene::getTankM()->addChild(this);
		this->scheduleUpdate();

//		AudioM::play2d(A_SHOW_BONUS);

		bRet = true;
	} while (false);
	return bRet;
}

void Bonus::update(float dt)
{
	if (isCollidePlayer())
	{
		switch (_type)
		{
		case hpUp:
			GameScene::getTankM()->getPlayerTank()->addHP();
			break;
		case powerUp:
			GameScene::getTankM()->getPlayerTank()->powerUp();
			break;
		case miss:
			GameScene::getTankM()->getPlayerTank()->missUp();
			break;
		case statusUp:
			GameScene::getTankM()->getPlayerTank()->statusUp();
			break;
		default:
			break;
		}
		GameScene::getTankM()->removeBonus();
	}

}

bool Bonus::isCollidePlayer()
{
	auto player = GameScene::getTankM()->getPlayerTank();
	if (player == nullptr)
	{
		return false;
	}
	auto boundingBox1 = player->getBoundingBox();
	auto boundingBox2 = this->getBoundingBox();
	/* 不使用intersectsRect，因为边缘重合的时候并不算 */
	return !(boundingBox1.getMaxX() <= boundingBox2.getMinX() ||
		boundingBox2.getMaxX() <= boundingBox1.getMinX() ||
		boundingBox1.getMaxY() <= boundingBox2.getMinY() ||
		boundingBox2.getMaxY() <= boundingBox1.getMinY());
}
