#include "PlayerTank.h"
#include "scene\GameScene.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


bool PlayerTank::collidePos(Vec2 pos) {
	auto overlap = false;
	auto &tanks = GameScene::getTankM()->getAllTanks();
	for (auto i = 0; i < tanks.size(); i++)
	{
		auto tank = tanks.at(i);
		if (tank == this) continue;
		auto otherPos = tank->getPosition();
		/* 坦克前端与另一坦克相交则改变行走方向（如果判断相交就改变方法则会发现两只坦克会一直在转圈） */
		if (pos.x > otherPos.x - 2 * CELL_WIDTH && pos.x < otherPos.x + 2 * CELL_WIDTH)
		{
			if (_direction == UP && pos.y > otherPos.y - 2 * CELL_HEIGHT && pos.y < otherPos.y)
			{
				overlap = true;
			}
			else if (_direction == DOWN && pos.y > otherPos.y && pos.y < otherPos.y + 2 * CELL_HEIGHT)
			{
				overlap = true;
			}
		}
		if (pos.y > otherPos.y - 2 * CELL_HEIGHT && pos.y < otherPos.y + 2 * CELL_HEIGHT)
		{
			if (_direction == LEFT && pos.x < otherPos.x + 2 * CELL_WIDTH && pos.x > otherPos.x)
			{
				overlap = true;
			}
			else if (_direction == RIGHT && pos.x < otherPos.x && pos.x > otherPos.x - 2 * CELL_WIDTH)
			{
				overlap = true;
			}
		}
	}
	return overlap;
}

void PlayerTank::speUp() {

	//加音效
	SimpleAudioEngine::getInstance()->playEffect("speBigSkill.mp3", false);

	Vec2 pos = _newPos;
	auto stage = GameScene::getStage();
	switch (_direction)
	{
	case UP: {
		//动画
		auto skinID = String::createWithFormat("playertank2_%d.png", DataM::getInstance()->getSkinId());
		Sprite * speup = Sprite::create(skinID->getCString());
		speup->setPosition(Vec2(0, -198));
		ActionInterval *moveto1 = MoveTo::create(0.7f, Vec2(0, 0));
		auto moveto2 = EaseExponentialOut::create(moveto1);
		ActionInterval *fadein = FadeOut::create(0.7f);
		this->addChild(speup, 2);
		auto spawnAction = Spawn::create(moveto2, fadein, NULL);
		auto sequenceAction = Sequence::create(spawnAction, DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, speup)), NULL);
		speup->runAction(sequenceAction);

		pos.y += 64 * jumpAbility;
		while (abs(pos.y - _newPos.y) > 3) {
			if ((int)pos.x % 32 == 0) {
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y) - 1, getColNumberFromPosition(pos.x))) { pos.y -= 5; continue; }
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x) - 1)) { pos.y -= 5; continue; }
			}
			if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x))) {
				pos.y -= 5;
				continue;
			}
			if (collidePos(pos) || overlapCheckPos(pos) ) {
				pos.y -= 5;
				continue;
			}
			_newPos = pos;
			this->setPosition(_newPos);
			break;
		}
		break;
	}
	case DOWN: {
		//动画
		auto skinID = String::createWithFormat("playertank2_%d.png", DataM::getInstance()->getSkinId());
		Sprite * speup = Sprite::create(skinID->getCString());
		speup->setRotation(180);
		speup->setPosition(Vec2(0, 198));
		ActionInterval *moveto1 = MoveTo::create(0.7f, Vec2(0, 0));
		auto moveto2 = EaseExponentialOut::create(moveto1);
		ActionInterval *fadein = FadeOut::create(0.7f);
		this->addChild(speup, 2);
		auto spawnAction = Spawn::create(moveto2, fadein, NULL);
		auto sequenceAction = Sequence::create(spawnAction, DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, speup)), NULL);
		speup->runAction(sequenceAction);

		pos.y -= 64 * jumpAbility;
		while (abs(pos.y - _newPos.y) > 3) {
			if ((int)pos.x % 32 == 0) {
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y) - 1, getColNumberFromPosition(pos.x) - 1)) { pos.y += 5; continue; }
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x) - 1)) { pos.y += 5; continue; }
			}
			if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x))) {
				pos.y += 5;

				continue;
			}
			if (collidePos(pos) || overlapCheckPos(pos)) {
				pos.y += 5;
				continue;
			}
			_newPos = pos;
			this->setPosition(_newPos);
			break;
		}
		break;
	}
	case LEFT: {
		//动画
		auto skinID = String::createWithFormat("playertank2_%d.png", DataM::getInstance()->getSkinId());
		Sprite * speleft = Sprite::create(skinID->getCString());
		speleft->setRotation(270);
		speleft->setPosition(Vec2(198, 0));
		ActionInterval *moveto1 = MoveTo::create(0.7f, Vec2(0, 0));
		auto moveto2 = EaseExponentialOut::create(moveto1);
		ActionInterval *fadein = FadeOut::create(0.8f);
		this->addChild(speleft, 2);
		auto spawnAction = Spawn::create(moveto2, fadein, NULL);
		auto sequenceAction = Sequence::create(spawnAction, DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, speleft)), NULL);
		speleft->runAction(sequenceAction);

		pos.x -= 64 * jumpAbility;
		while (abs(pos.x - _newPos.x) > 3) {
			if ((int)pos.y % 32 == 0) {
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y) - 1, getColNumberFromPosition(pos.x))) { pos.x += 5; continue; }
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x) + 1)) { pos.x += 5; continue; }
			}
			if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x))) {
				pos.x += 5;

				continue;
			}
			if (collidePos(pos) || overlapCheckPos(pos)) {
				pos.x += 5;
				continue;
			}
			_newPos = pos;
			this->setPosition(_newPos);
			break;
		}
		break;
	}
	case RIGHT: {
		//动画
		auto skinID = String::createWithFormat("playertank2_%d.png", DataM::getInstance()->getSkinId());
		Sprite * speright = Sprite::create(skinID->getCString());
		speright->setRotation(90);
		speright->setPosition(Vec2(-198, 0));
		ActionInterval *moveto1 = MoveTo::create(0.7f, Vec2(0, 0));
		auto moveto2 = EaseExponentialOut::create(moveto1);
		ActionInterval *fadein = FadeOut::create(0.8f);
		this->addChild(speright, 2);
		auto spawnAction = Spawn::create(moveto2, fadein, NULL);
		auto sequenceAction = Sequence::create(spawnAction, DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, speright)), NULL);
		speright->runAction(sequenceAction);

		pos.x += 64 * jumpAbility;
		while (abs(pos.x - _newPos.x) > 3) {
			if ((int)pos.y % 32 == 0) {
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y) - 1, getColNumberFromPosition(pos.x))) { pos.x -= 5; continue; }
				if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x) - 1)) { pos.x -= 5; continue; }
			}
			if (!stage->isCanWalk(getRowNumberFromPosition(pos.y), getColNumberFromPosition(pos.x))) {
				pos.x -= 5;

				continue;
			}
			if (collidePos(pos) || overlapCheckPos(pos)) {
				pos.x -= 5;
				continue;
			}
			_newPos = pos;
			this->setPosition(_newPos);
			break;
		}
		break;
	}
	}
}

PlayerTank::PlayerTank() {
}

PlayerTank::~PlayerTank() {
}

PlayerTank* PlayerTank::create(HeroType heroType)
{
	PlayerTank *pRet = new PlayerTank();
	if (pRet && pRet->init(heroType))
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

bool PlayerTank::init(HeroType heroType)
{
	bool bRet = false;
	do
	{
		Sprite::init();

		_heroType = heroType;
		HP = TankData::getInstance()->getHP();
		SPE = TankData::getInstance()->getSPE();
		ATK = TankData::getInstance()->getATK();
		bulletNumMAX = TankData::getInstance()->getBulletNumMAX();
		isAOE = TankData::getInstance()->isAOE();
		AvoidProbability = TankData::getInstance()->getAvoidProbability();
		DamageDiscount = TankData::getInstance()->getDamageDiscount();
		bulletSPE = TankData::getInstance()->getBulletSPE();
		bulletDistance = TankData::getInstance()->getBulletDistance();
		shieldTime = TankData::getInstance()->getShieldTime();
		jumpAbility = TankData::getInstance()->getJumpAbility();
		isRebirth = TankData::getInstance()->isRebirth();
		atkInterval = TankData::getInstance()->getAtkInterval();
		isAOE = TankData::getInstance()->isAOE();
		FireUp = TankData::getInstance()->isFireUp();

		isShield = false;

		String *tankSkinName = String::createWithFormat("playertank%d_%d.png", int(DataM::getInstance()->getHType()), DataM::getInstance()->getSkinId());
		Sprite *tankSkin = Sprite::create(tankSkinName->getCString());
		this->addChild(tankSkin, 0, "tankSkin");

		this->initPos();
		this->scheduleUpdate();
		bRet = true;
	} while (false);
	return bRet;
}

void PlayerTank::initPos()
{

	this->setPos(Vec2(MAP_ORIGIN.x + 11 * 32, MAP_ORIGIN.y + 32),UP);
}

void PlayerTank::update(float dt)
{

	//_dt = dt;
	auto state = GameScene::getGameState();
	if (state == kPause || state == kFail)
	{
		return;
	}
	//_shootInterval += dt;
	if (g_keyUp)
	{
		//_move = true;
		if (_direction == UP)
		{
			moveUp();
		}
		else
		{
			turnUp();
		}
	}
	else if (g_keyDown)
	{
		//_move = true;
		if (_direction == DOWN)
		{
			moveDown();
		}
		else
		{
			turnDown();
		}
	}
	else if (g_keyLeft)
	{
		//_move = true;
		if (_direction == LEFT)
		{
			moveLeft();
		}
		else
		{
			turnLeft();
		}
	}
	else if (g_keyRight)
	{
		//_move = true;
		if (_direction == RIGHT)
		{
			moveRight();
		}
		else
		{
			turnRight();
		}
	}
	//else
	//{
	//	_move = false;
	//	trackSlip();
	//}

	//if (_moveAudioId != AudioM::INVALID_AUDIO_ID && _move == false)
	//{
	//	this->stopMoveAudio();
	//}
	//else if (_moveAudioId == AudioM::INVALID_AUDIO_ID && _move == true)
	//{
	//	this->playMoveAudio();
	//}

	if (g_keyA)
	{
		//NotificationCenter::getInstance()->postNotification("game_win");
		if (DataM::getInstance()->getHType() == TypeSPE && atkInterval != 0) {
			g_keyA = false;
			return;
		}
		atkInterval = TankData::getInstance()->getAtkInterval();
		bool isShoot = shoot();

		if (isShoot)
		{
			//子弹成就
			SuccessData::getInstance()->updateBulletNum();

			//加音效
			switch (DataM::getInstance()->getHType())
			{
			case TypeATK:	
				if (isAOE)
				{
					SimpleAudioEngine::getInstance()->playEffect("atkAttackWithAOE.mp3", false);

				}
				else
				{ 
					SimpleAudioEngine::getInstance()->playEffect("atkAttack.mp3", false);
				}
				break;
			case TypeDEF:
				SimpleAudioEngine::getInstance()->playEffect("defAttack.mp3", false);
				break;
			case TypeSPE:
				SimpleAudioEngine::getInstance()->playEffect("speAttack.mp3", false);
				break;
			default:
				break;
			}

		}
		
		//if (DataM::getInstance()->getHType() == TypeSPE)	atkInterval = 
		g_keyA = false;
		/*if (_shootInterval > 0.1f)
		{
		_shootInterval = 0.0f;*/

		/*}*/
	}
	//if (g_keyB && GameScene::isKReady()) {
	if (g_keyB && GameScene::getStage()->changeIsKReady()) {
		g_keyB = false;

		//大招成就
		SuccessData::getInstance()->updateBigSkillTime();

		HeroType type = _heroType;
		switch (type)
		{
		case TypeATK:
			dieCountAll();
			break;
		case TypeDEF:
			shieldOn();
			break;
		case TypeSPE:
		{	speUp();
			break;
		}
		default:
			break;
		}
	}
	if (overlapCheck())
	{
		_newPos = _position;
	}
	collideMap();
	collideTank();

	if (rand() % 1000 == 199) {
		unsigned int x = rand() % 3;
		unsigned int randNum = rand() % 7;
		switch (DataM::getInstance()->getHType())
		{
		case TypeATK:
			SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("atk%d.mp3",randNum)->getCString(), false);
			break;
		case TypeDEF:
			//缺失音效 音效缺失
			SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("def%d.mp3", randNum)->getCString(), false);
			break;
		case TypeSPE:
			//SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("atk%d.mp3", randNum)->getCString(), false);
			break;
		default:
			break;
		}
	}
	
	if (DataM::getInstance()->getHType() == TypeSPE && atkInterval > 0) {
		atkInterval--;
	}
	
		
	
	//uto spriteFrameName = String::createWithFormat("player1_%d_%d_%d.png", _level, _direction, _step + 1)->getCString();
	//auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
	//this->setSpriteFrame(frame);
	this->setPosition(_newPos);
}

void PlayerTank::pauseGame()
{
	_scheduler->pauseTarget(this);
//	if (_shield)
//	{
//		_shield->setVisible(false);
//	}
}

void PlayerTank::resumeGame()
{
	_scheduler->resumeTarget(this);
}

void PlayerTank::hit(int atk) //tank->hit()
{
	if (isShield) return;
	//if (rand() % 10 < AvoidProbability * 10 {  此处为旭阳改
	if (rand() % 100 < AvoidProbability * 100) {
		this->setOpacity(50);
		isAvoid = true;
		this->unschedule("avoid");
		this->scheduleOnce([&](float dt) {
			isAvoid = false;
			this->setOpacity(255);
		}, 2.0f, "avoid");
		return;
	}
	//{
	//	this->stopMoveAudio();
	//	AudioM::play2d(A_PLAYER_BOMB);
	//	GameScene::getBombM()->createBomb(kPlayerTankBomb, _position);
	//}

	atk -= DamageDiscount;
	this->HP -= atk;

	//加音效
	unsigned int randNum = rand() % 2;
	SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("hit%d.mp3", randNum)->getCString(), false);

	if (this->HP < 1) {
		this->HP = 0;
		if (DataM::getInstance()->getHType() == TypeDEF && isRebirth == true) {
			isRebirth = false;
			this->HP += 100;

			//十字架
			Sprite *cross = Sprite::create("Cross.png");
			this->addChild(cross, 1, "cross");
			FadeOut *fadeOut = FadeOut::create(1.0f);
			auto seq = Sequence::create(DelayTime::create(2.0f), fadeOut, CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, cross)), NULL);
			cross->runAction(seq);

			//加音效
			SimpleAudioEngine::getInstance()->playBackgroundMusic("defRebirth.mp3", false);

			return;
		}

		//死亡成就
		SuccessData::getInstance()->updateDeathTime();

		//指针置空
		GameScene::getTankM()->set_playerTank(nullptr);
		GameScene::getTankM()->removeTank(this);

		//游戏结束
	}
}

void PlayerTank::shieldOn() {
	isShield = true;
	//_shield=Sprite::cre

	//加音效
	unsigned int randNum = rand() % 2;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("defShield%d.mp3", randNum)->getCString(), false);


	//护盾图片加载
	Sprite *shieldImage = Sprite::create("Sheild.png");
	shieldImage->setPosition(0, 0);
	this->addChild(shieldImage, 1, "sheildImage");
	auto scaleShield1 = ScaleTo::create(0.2f, 1.2f);
	auto scaleShield2 = ScaleTo::create(0.2f, 1.0f);
	Sequence *scaleShieldSeq = Sequence::create(scaleShield1, scaleShield2, NULL);
	auto scaleShieldSeqForever = RepeatForever::create(scaleShieldSeq);
	shieldImage->runAction(scaleShieldSeqForever);
	//this->runAction(Blink::create(10.0f, 30));
	//_shield = Sprite::createWithSpriteFrameName("shield_01.png");
	//Vector<SpriteFrame*> animFrames(2);
	//auto cache = SpriteFrameCache::getInstance();
	//for (int i = 1; i < 3; i++)
	//{
	//	auto name = String::createWithFormat("shield_%02d.png", i)->getCString();
	//	auto frame = cache->getSpriteFrameByName(name);
	//	animFrames.pushBack(frame);
	//}
	//auto animation = Animation::createWithSpriteFrames(animFrames, 0.03f);
	//_shield->runAction(RepeatForever::create(Animate::create(animation)));
	//_shield->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->unschedule("shield");
	this->scheduleOnce([&](float dt) {
		//_shield->removeFromParent();
		//_shield = nullptr;
		isShield = false;

		//护盾图片删除
		Sprite *shieldImage = static_cast<Sprite *>(this->getChildByName("sheildImage"));
		shieldImage->removeFromParentAndCleanup(true);
	}, shieldTime, "shield");
}

void PlayerTank::addHP() {
	this->HP += 50;
	if (HP > TankData::getInstance()->getHP())	HP = TankData::getInstance()->getHP();
	return;
}

void PlayerTank::powerUp() {
	this->bulletPower = 1 ;
}

void PlayerTank::missUp() {
	auto miss = TankData::getInstance()->getAvoidProbability();
	miss = 1.0f;
	this->unschedule("missUp");
	this->scheduleOnce([&](float dt) {
		this->setAvo(TankData::getInstance()->getAvoidProbability());
	}, 10.0f, "missUp");
}

void PlayerTank::statusUp() {
	auto atk = GameScene::getTankM()->getPlayerTank()->getATK();
	auto spe = GameScene::getTankM()->getPlayerTank()->getSPE();
	GameScene::getTankM()->getPlayerTank()->setATK(atk + 2);
	GameScene::getTankM()->getPlayerTank()->setSPE(spe + 2);
}

void PlayerTank::dieCountAll() {
	//AudioM::play2d("atk_50.mp3");
	for (auto &x : GameScene::getTankM()->getEnemyTanks()) {
		x->dieCountBegin();
	}

	SimpleAudioEngine::getInstance()->playEffect("atkBigSkill.mp3", false);

}

bool PlayerTank::overlapCheckPos(Vec2 pos)
{
	auto overlap = false;
	auto &tanks = GameScene::getTankM()->getAllTanks();
	for (auto i = 0; i < tanks.size(); i++)
	{
		auto tank = tanks.at(i);
		if (tank == this) continue;
		auto otherPos = tank->getPosition();
		if (pos.x > otherPos.x - 2 * CELL_WIDTH && pos.x < otherPos.x + 2 * CELL_WIDTH)

			if (pos.y > otherPos.y - 2 * CELL_HEIGHT && pos.y < otherPos.y + 2 * CELL_HEIGHT)
				overlap = true;
	}
	return overlap;
}
