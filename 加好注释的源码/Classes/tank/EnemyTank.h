#pragma once
/*这个类是敌方坦克类，主要的函数有设置敌方坦克的属性，还有坦克的血条和最大数目，继承坦克类*/
#include "Tank.h"
#include "ui\CocosGUI.h"
using namespace ui;
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
/* 敌人坦克类 */
class EnemyTank : public Tank
{
public:
	EnemyTank();
	~EnemyTank();
	static EnemyTank* create(int type, Vec2 pos);
	bool init(int type, Vec2 pos);
	virtual void hit(int atk);
	void dieCountBegin();
	bool setFireUp() { isFireUp = true; }

private:
	void update(float dt);

	//bool _bonus;		// 是否有道具奖励 
	//int _bonusStep;	    // 带奖励的坦克的帧数 
	int _type;//类型
	float dieScale = 1;
	bool dieCountOn = false;
	bool isFireUp = false;//是否灼烧
	int count = 359;  //灼烧计数
	Sprite *diecount = nullptr;
	//最大生命值，用来计算进度条
	int fullHP;
	Slider *enemyHPSlider;

};

