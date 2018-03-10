#pragma once
#include "cocos2d.h"
#include "data/Global.h"
#include "media\AudioM.h"
#include "media\BombM.h"
/*该类为子弹类，主要的函数有创建子弹的函数，还有子弹移动过程中的碰撞检测，
有与地图边界、地图障碍物、子弹、坦克这四种判断检测*/
USING_NS_CC;

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();
	/**
	* 创建子弹
	* owner 子弹所属的坦克
	* speed 子弹速度
	* power 子弹力量 0不可打破铁，可打破半块砖；1可打破铁，可打破整块砖
	* pos 子弹位置
	* direction 子弹方向
	*/
	static Bullet* create(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance);
	bool init(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance);
	/* 获取该子弹所属的坦克 */
	void* getOwner() { return _owner; }

private:
	void update(float dt);
	/* 移动 */
	void move();
	/* 碰撞检测 */
	void collide();
	/* 与地图(地图边界及障碍物)的碰撞检测 */
	void collideMap();
	/* 与地图边界的碰撞检测 */
	void collideBorder();
	/* 与地图障碍物的碰撞检测 */
	void collideObstacle();
	/* 与子弹的碰撞检测 */
	void collideBullet();
	/* 与坦克的碰撞检测 */
	void collideTank();
	/* AOE检测 */
	void checkAOE();
	
	void* _owner;				// 发出该子弹的坦克 
	float _speed;				// 子弹的速度 
	int _power=0;				// 子弹的强度（0不能打铁 1可以打铁） 
	Vec2 _newPos;				// 子弹下一帧的位置 
	Direction _direction;		// 子弹的位置 
	Vec2 _bombPos;				// 子弹爆炸的位置 
	bool _bomb;					// 子弹是否爆炸 
	float _dt;					// 两帧之间的时间间隔 
	int _distance;				 //子弹飞行距离	
	float Bullet_p_x;			//子弹发射x坐标
	float Bullet_p_y;			//子弹发射y坐标
	int atk;					//该子弹的攻击力
};