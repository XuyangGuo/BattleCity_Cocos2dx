#pragma once
/*这个类是坦克类，是玩家坦克和敌方坦克的父类，主要的函数有坦克移动函数、设计函数
还有与地图、坦克的碰撞检测*/
#include "cocos2d.h"
#include "data\Global.h"
#include "data\DataM.h"
#include "input\keyboardInput.h"
#include "data\TankData.h"

class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
USING_NS_CC;
class Tank : public Sprite {
public:
	Tank();
	~Tank();
	virtual bool init();
	//int getType() { return _type; }
	/* 被子弹打到 */
	virtual void hit(int atk)=0;
	/*得到坦克的HP*/
	int getHP() { return HP; }
	float getSPE() { return SPE; }
	//得到坦克的攻击力
	int getATK() { return ATK; }
	//得到坦克的子弹数目
	int getBulletNum() { return bulletNumMAX; }
	//得到坦克的速度
	void setSPE(float spe) { SPE = spe;}
	//设置坦克的攻击力
	void setATK(int atk) { ATK = atk; }


protected:
	/* 初始化位置 */
	void initPos();
	/* 设置位置和方向 */
	void setPos(Vec2 pos, Direction direction);
	/* 向上移动	*/
	void moveUp();
	/* 向右移动	*/
	void moveRight();
	/* 向下移动	*/
	void moveDown();
	/* 向左移动	*/
	void moveLeft();
	/* 方向转为向上	*/
	void turnUp();
	/* 方向转为向右	*/
	void turnRight();
	/* 方向转为向下	*/
	void turnDown();
	/* 方向转为向左	*/
	void turnLeft();
	/* 由左右移动改为上下移动时，调整x坐标 */
	void adjustPosX();
	/* 由上下移动改为左右移动时，调整y坐标 */
	void adjustPosY();
	/* 与地图的碰撞检测 */
	bool collideMap();
	/* 与坦克的碰撞检测 */
	bool collideTank();
	/* 检测是否与其它坦克重叠 */
	bool overlapCheck();
	/* 发射子弹 */
	bool shoot();
//	/* 行走动画帧数增加 */
//	void addStep();


	Vec2 _newPos;			//移动后的坐标
	Direction _direction;	// 方向 
	float _dt;

	int HP;//设置HP
	float SPE;//设置速度
	int ATK;//设置攻击力
	int bulletNumMAX;//设置子弹最大数目
	float bulletSPE;//设置子弹速度
	float bulletDistance;//设置子弹射程
	int bulletPower = 0;		// 子弹的威力(0不可打破铁，1可打破铁) 
	bool isAvoid = false;//设置是否闪避
};