/***********************************************

该类是进行游戏的场景，用来管理当前游戏的运行状态，
管理坦克类、子弹类、爆炸类的生命周期

***********************************************/

#pragma once
#include "cocos2d.h"
#include "tank\TankM.h"
#include "stage\Stage.h"
#include "stage\WinLayer.h"
#include "stage\FailLayer.h"
#include "tank\BulletM.h"
#include "media\AudioM.h"
#include "media\BombM.h"

USING_NS_CC;
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
enum GameState
{
	kRuning,  // 进行中
	kPause,   //暂停
	kWin,     //胜利
	kFail,   //失败
	kNone,
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	/* 获取坦克管理类对象 */
	static TankM *getTankM() { return _tankM; }
	static Stage *getStage() { return _stage; }
	static BulletM *getBulletM() { return _bulletM; }
	static BombM* getBombM() { return _bombM; }
	static GameState getGameState() { return _gameState; }
	static bool isKReady();
private:
	void onExit();
	void onEnterTransitionDidFinish();
	static TankM *_tankM;  //GameScene的坦克管理类单例
	static Stage *_stage;	//GameScene的Stage单例
	static BulletM *_bulletM;  //GameScene的bullet管理类单例
	static BombM *_bombM;  //GameScene的bombM管理类单例
	static GameState _gameState;  //游戏进行状态
	WinLayer *winLayer;				//胜利层
	FailLayer *failLayer;			//失败层

	void showFinishedSuccess();

	/* 关卡胜利 */
	void win(Ref* pSender);
	/* 关卡失败 */
	void fail(Ref* pSender);
	/* Update */
	void update(float dt);
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 成就 */
	std::vector<char *> currentFinished;

};