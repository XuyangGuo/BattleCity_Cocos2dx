#pragma once
#include "cocos2d.h"
#include "Bomb.h"
USING_NS_CC;
/* 爆炸管理类 */
class BombM : public Layer
{
public:
	BombM();
	~BombM();
	CREATE_FUNC(BombM);
	/**
	* 创建爆炸
	* type 爆炸类型
	* pos 爆炸位置
	*/
	void createBomb(BombType type, Vec2 pos);
	/* 暂停游戏（暂停播放所有爆炸动画） */
	void pauseGame();
	/* 继续游戏（继续播放所有爆炸动画） */
	void resumeGame();
};
