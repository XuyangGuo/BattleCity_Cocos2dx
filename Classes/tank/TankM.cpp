 #include "TankM.h"
#include "scene\GameScene.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
/*****************************************
这个类是坦克管理类，主要的功能就是提供创建坦克的接口，并有暂停游戏和移除坦克的函数
*****************************************/

//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


TankM::TankM() {
	/* 监听开场音效结束事件，开场音效结束后才开始播放敌人坦克行走音效 */
	//NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(TankM::startAudioEnd), "start_audio_end", nullptr);
}
 
TankM::~TankM(){
	//NotificationCenter::getInstance()->removeAllObservers(this);
}
//创建坦克
bool TankM::init()
{
	bool bRet = false;
	curEnemyId = 0;
	bonus = nullptr;
	do
	{
		//_pos = POS_MIDDLE;
		this->createNewPlayer();
		this->schedule(CC_SCHEDULE_SELECTOR(TankM::timer), 2.7f, kRepeatForever, 0.001f);

		bRet = true;
	} while (false);
	return bRet;
}
//定时器来创建坦克
void TankM::timer(float dt)
{
	this->createNewEnemy();
	//GameScene::getStage()->updateEnemyNum();
}
//创建玩家坦克
void TankM::createNewPlayer()
{
	_playerTank = PlayerTank::create(DataM::getInstance()->getHType());
	this->addChild(_playerTank);
	_tanks.pushBack(_playerTank);
}

//创建敌方坦克，坦克的最大数目为6
void TankM::createNewEnemy()
{
		_pos++;
		if (_pos >= 3)	_pos = 0;
	//auto bore = this->createBore([&](Node* sender) {
		auto stage = GameScene::getStage();
		//auto tank = EnemyTank::create(stage->getEnemyType(), sender->getPosition());
		auto tank = EnemyTank::create(stage->getEnemyType(), Vec2(MAP_ORIGIN.x + (_pos * 13 + 1) * 32, MAP_ORIGIN.y + 17 * CELL_HEIGHT));
		this->addChild(tank);
		_tanks.pushBack(tank);
		_enemyTanks.pushBack(tank);
		if (_enemyTanks.size() == 6)
		{
			this->unschedule(CC_SCHEDULE_SELECTOR(TankM::timer));
		}
		curEnemyId++;

		if (curEnemyId == ENEMY_NUM)
		{
			this->unschedule(CC_SCHEDULE_SELECTOR(TankM::timer));
		}
	//});
	//this->addChild(bore, 1);


}
//设置暂停游戏的接口
void TankM::pauseGame()
{
	_scheduler->pauseTarget(this);
	////for (auto child : this->getChildren())
	////{
	////	if (child->getName() == "bore")
	////	{
	////		child->pause();
	////	}
	////}
	//if (_playerTank)
	//{
	//	_playerTank->pauseGame();
	//}
	auto &tanks = this->getAllTanks();
	for (auto tank : tanks) {
		tank->pause();
	}
}
//设置重新游戏的接口
void TankM::resumeGame()
{
	_scheduler->resumeTarget(this);
	//for (auto child : this->getChildren())
	//{
	//	if (child->getName() == "bore")
	//	{
	//		child->resume();
	//	}
	//}
	//if (_playerTank)
	//{
	//	_playerTank->resumeGame();
	//}
	auto &tanks = this->getAllTanks();
	for (auto tank : tanks) {
		_scheduler->resumeTarget(tank);
	}
}
//当坦克死亡时，创建爆炸，并移除坦克
void TankM::removeTank(Tank* tank)
{
	//加音效
	unsigned int randNum = rand() % 7;
	SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("removeTank%d.mp3", randNum)->getCString(), false);

	GameScene::getBombM()->createBomb(kTankBomb, tank->getPosition());
	if (tank == _playerTank)
	{
		_playerTank = nullptr;
	}
	else
	{
		//坦克成就
		SuccessData::getInstance()->updateHitTankNum();

//		AudioM::play2d(A_ENEMY_BOMB);
		if ((rand() % 4 == 0))
		{
			if (bonus == nullptr) bonus = Bonus::create((BonusType)(rand() % 4 + 1), tank->getPosition());
			//this->scheduleOnce( , 10.0f, "missUp");
		}
		_enemyTanks.eraseObject((EnemyTank*)tank);
		if (curEnemyId < ENEMY_NUM && _enemyTanks.size() != 4)
		{
			this->schedule(CC_SCHEDULE_SELECTOR(TankM::timer), 2.7f, kRepeatForever, 0.5f);
		}
	}
	_tanks.eraseObject(tank);
	tank->removeFromParent();
	if (curEnemyId == ENEMY_NUM && _enemyTanks.size() == 0)
	{
		if (GameScene::getGameState() == kRuning)
		{
			//this->stopEnemyMoveAudio();
			NotificationCenter::getInstance()->postNotification("game_win");
		}
	}
	if (_playerTank==nullptr) NotificationCenter::getInstance()->postNotification("game_fail");
}
//打死所有的敌方坦克
void TankM::killAllEnemy()
{
	for (auto i = _enemyTanks.size() - 1; i >= 0; i--)
	{
		auto enemy = _enemyTanks.at(i);
		removeTank(enemy);
	}
}
//当坦克吃到道具的时候，移除道具
void TankM::removeBonus() {
	bonus->removeFromParent();
	bonus = nullptr;
}
