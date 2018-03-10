/***********************************************

该类用来创建爆炸动画

***********************************************/

#include "Bomb.h"
#include <string>
#include "scene/GameScene.h"

using namespace std;

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

Bomb* Bomb::create(BombType type)
{
	Bomb *pRet = new Bomb();
	if (pRet && pRet->init(type))
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

bool Bomb::init(BombType type) 
{
	bool bRet = false;
	do
	{
		_type = type;
		string name;
		int size;
		switch (_type)
		{
		case kTankBomb:
		///*case kStrongholdBomb:*/
			name = "tankbomb";
			size = 4;
			break;
		case kBulletBomb:
			name = "bulletbomb";
			size = 1;
			break;
		default:
			break;
		}
		auto str = String::createWithFormat("%s_01.png", name.c_str())->getCString();
		this->initWithSpriteFrameName(str);

		Vector<SpriteFrame*> animFrames(size);
		auto cache = SpriteFrameCache::getInstance();

		for (auto i = 1; i < size + 1; i++)
		{
			auto str = String::createWithFormat("%s_%02d.png", name.c_str(), i)->getCString();
			auto frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.12f);
		auto action = Sequence::create(
			Animate::create(animation),
			RemoveSelf::create(),
			/*CallFuncN::create(CC_CALLBACK_1(Bomb::bombEnd, this)),*/
			nullptr);
		this->runAction(action);

		bRet = true;
	} while (false);
	return bRet;
}