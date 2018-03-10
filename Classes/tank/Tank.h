#pragma once

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
	int getHP() { return HP; }
	float getSPE() { return SPE; }
	int getATK() { return ATK; }
	int getBulletNum() { return bulletNumMAX; }
	void setSPE(float spe) { SPE = spe;}
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

	int HP;
	float SPE;
	int ATK;
	int bulletNumMAX;
	float bulletSPE;
	float bulletDistance;
	int bulletPower = 0;		// 子弹的威力(0不可打破铁，1可打破铁) 
	bool isAvoid = false;
};