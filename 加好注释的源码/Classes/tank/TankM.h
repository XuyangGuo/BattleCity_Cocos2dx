#pragma once
/*****************************************
这个类是坦克管理类，主要的功能就是提供创建坦克的接口，并有暂停游戏和移除坦克的函数
*****************************************/
#include "cocos2d.h"
#include "data\Global.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bonus.h"
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
USING_NS_CC;

using namespace std;
class TankM : public Layer
{
public:
	TankM();
	~TankM();
	CREATE_FUNC(TankM);
	bool init();
	/* 获取玩家坦克 */
	PlayerTank* getPlayerTank() { return _playerTank;}
	/* 获取敌人坦克 */
	Vector<EnemyTank*>& getEnemyTanks() { return _enemyTanks; }
	/* 获取所有坦克 */
	Vector<Tank*>& getAllTanks() { return _tanks; }
	
	/*创建道具*/
	Bonus* bonus;
	void removeBonus();
	/* 删除坦克 */
	void removeTank(Tank* tank);
	/* 杀死所有敌人坦克 */
	void killAllEnemy();

	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 用来updateSlider 值域为0到100 */
	int remainedHP() { 
		if (_playerTank != nullptr)
		{
			return static_cast<int>(100 * ((float)_playerTank->getHP() / (float)TankData::getInstance()->getHP()));
		}
		else
			return 0;
	}
	/* 用来updateSlider 值域为0到100 */
	int getProgress() { return static_cast<int>(100 * ((float)curEnemyId / (float)ENEMY_NUM));}

	int EnemyTankNum() { return _enemyTanks.size(); }

	/* 更改_playerTank,主要考虑到玩家HP的安全检测 */
	void set_playerTank(PlayerTank* playerTank) { _playerTank = playerTank; }


private:
	/* 定时器回调（出现新的敌人坦克） */
	void timer(float dt);
	/* 创建新的玩家坦克 */
	void createNewPlayer();
	/* 创建新的敌人坦克 */
	void createNewEnemy();

	int _pos=0;								// 敌人坦克出现的位置 
	PlayerTank* _playerTank;				// 玩家坦克 
	Vector<EnemyTank*> _enemyTanks;			// 敌人坦克 
	Vector<Tank*> _tanks;					// 所有坦克 
	int curEnemyId;							// 敌人坦克是否全部出现 

};