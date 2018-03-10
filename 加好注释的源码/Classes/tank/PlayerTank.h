#pragma once
/*这是玩家坦克的类，主要的功能就是继承坦克类，同时又对坦克放大招进行实现，还有坦克属性加成的函数*/
#include "Tank.h"
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
class PlayerTank : public Tank
{
public:
	PlayerTank();
	~PlayerTank();
	static PlayerTank* create(HeroType heroType);
	virtual void hit(int atk);
	bool init(HeroType type);

	void setAvo(float avo) { AvoidProbability = avo; }
	/* 初始化位置 */
	void initPos();

	/* 游戏暂停 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/*Bonus*/
	void addHP();//加血
	void powerUp();//加力量
	void missUp();//加闪避
	void statusUp();//加buff
	bool FireUpStatus() { return FireUp; }//是否有灼烧的效果


private:
	void update(float dt);
	void shieldOn();//无敌
	void speUp();//加速
	void dieCountAll();//清除所有坦克
	bool collidePos(Vec2 pos);//
	bool overlapCheckPos(Vec2 pos);

	Sprite* _shield;
	HeroType _heroType;
	float AvoidProbability;

	bool isShield = false;
	bool isAOE;
	bool FireUp = false;				
	int DamageDiscount;			//int
	
	float shieldTime=5.0;
	int jumpAbility=3;//加速能力
	bool isRebirth = false;
	int atkInterval=0;

	Vec2 _oldpos;				//for speUP()

	
};