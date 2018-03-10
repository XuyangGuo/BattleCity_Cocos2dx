#include "EnemyTank.h"
#include "scene\GameScene.h"

EnemyTank::EnemyTank() {

}

EnemyTank::~EnemyTank(){

}

EnemyTank* EnemyTank::create(int type, Vec2 pos)
{
	EnemyTank *pRet = new EnemyTank();
	if (pRet && pRet->init(type, pos))
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

bool EnemyTank::init(int type, Vec2 pos)
{
	bool bRet = false;
	do
	{
		Sprite::init();
		_type = type;
		_direction = DOWN;
		this->setPosition(pos);
		_newPos = pos;
		bulletDistance = 1000;
		switch (_type)
		{
		case 1:
			ATK = 10;
			HP = 40;
			SPE = 1.5;
			bulletSPE = 8;
			bulletNumMAX = 1;
			break;
		case 2:  //速度快
			ATK = 15;
			HP = 60;
			SPE = 3;
			bulletSPE = 8;
			bulletNumMAX = 1;
			break;
		case 3:  //血厚
			ATK = 20;
			HP = 150;
			SPE = 1.8;
			bulletSPE = 8;
			bulletNumMAX = 1;
			break;
		case 4:  //攻击高
			ATK = 30;
			HP = 90;
			SPE = 3;
			bulletSPE = 12;
			bulletNumMAX = 2;
			break;
		case 5:  //大Boss
			ATK = 70;
			HP = 270;
			SPE = 4.5;
			bulletSPE = 12;
			bulletNumMAX = 3;
		default:
			break;
		}
		fullHP = HP;

		String *enemyTankName = String::createWithFormat("EnemyTank%d.png", _type);
		Sprite *enmeyTankImage = Sprite::create(enemyTankName->getCString());
		this->addChild(enmeyTankImage, 1, "enemyTankImage");

		//敌方坦克血条
		enemyHPSlider = Slider::create();
		enemyHPSlider->loadProgressBarTexture("EnemyTankHPFull.png");
		enemyHPSlider->loadBarTexture("EnemyTankHPEmpty.png");
		this->addChild(enemyHPSlider, 1);
		enemyHPSlider->setPercent(100);
		enemyHPSlider->setPosition(Vec2(0, CELL_HEIGHT + 14));
		enemyHPSlider->setTouchEnabled(false);

		this->scheduleUpdate();
		bRet = true;
	} while (false);
	return bRet;
}

void EnemyTank::update(float dt)
{
	//更新血条
	int hpPercent = (int)(HP * 100 / fullHP);
	if (hpPercent < 0)
	{
		hpPercent = 0;
	}
	if (hpPercent > 100)
	{
		hpPercent = 100;
	}
	enemyHPSlider->setPercent(hpPercent);
	//_dt = dt;
	//if (!GameScene::getTankM()->isHaltEnemy() && GameScene::getGameState() != kPause)

	if(true)
	{
		switch (_direction)
		{
		case UP:
			this->moveUp();
			break;
		case DOWN:
			this->moveDown();
			break;
		case LEFT:
			this->moveLeft();
			break;
		case RIGHT:
			this->moveRight();
			break;
		default:
			break;
		}
		if (collideMap() || collideTank() || overlapCheck() || rand() % 40 == 0)
		{
			switch (rand() % 4)
			{
			case 0:
				turnUp();		
				break;
			case 1:
				turnDown();
				break;
			case 2:
				turnLeft();
				break;
			case 3:
				turnRight();
				break;
			default:
				break;
			}
		}
		if (rand() % 80 == 0)
		{
			shoot();
		}
	}
	//int step;
	//if (_bonus)
	//{
	//	step = _stepMax * _bonusStep + _step % (_bonusStep + 1) + 1;
	//}
	//else
	//{
	//	step = _step + 1;
	//}
	//auto spriteFrameName = String::createWithFormat("enemy%d_%d_%d_%d.png", _type, _level, _direction, step)->getCString();
	//SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
	//this->setSpriteFrame(frame);
	
	
	//下面的代码置于函数最后 

	//此处有BUG,count每次执行到这里都是300，所以把count放在init()中初始化
	//if (isFireUp) count = 300;

	if (isFireUp)
	{
		if (count > 0 && count % 60 == 0) {
			this->HP -= 20;
		}
		count--;
		if (count <= 0)
		{
			this->removeChildByName("bornSprite");
			isFireUp = false;
		}
	}

	this->setPosition(_newPos);
	if (dieCountOn == true) {
		if (dieScale > 0.5) {
			dieScale -= 0.003;
			diecount->setScale(dieScale);
		}
		else
			this->HP = 0;
	}
	if (this->HP < 1) {
		GameScene::getTankM()->removeTank(this);
	}
}

void EnemyTank::hit(int atk) {
	//if (_bonus)
	//{
	//	GameScene::getStage()->createBonus((BonusType)(rand() % 6 + 1));
	//}
	if (GameScene::getTankM()->getPlayerTank()->FireUpStatus() == true) {
		
		//加入灼烧动画
		if (false == isFireUp)
		{
			Sprite *bornSprite = Sprite::create("Born0.png");
			this->addChild(bornSprite, 2, "bornSprite");
			auto bornScale1 = ScaleTo::create(0.2f, 0.8f);
			auto bornScale2 = ScaleTo::create(0.2f, 1.0f);
			Sequence *bornSequence = Sequence::create(bornScale1, bornScale2, NULL);
			auto bornSequenceForveer = RepeatForever::create(bornSequence);
			bornSprite->runAction(bornSequenceForveer);
		}
		isFireUp = true;
	}
	this->HP -= atk;
	if (this->HP < 1) {
		GameScene::getTankM()->removeTank(this);
	}

	count = count % 60 + 300;  //重置灼烧计数
}

void EnemyTank::dieCountBegin() {
	diecount = Sprite::create("diecount.png");
	diecount->setPosition(0, 0);
	this->addChild(diecount);
	dieScale = 1;
	dieCountOn = true;
}