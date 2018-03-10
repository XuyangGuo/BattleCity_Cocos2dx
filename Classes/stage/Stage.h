#pragma once
#include "cocos2d.h"
#include "data\Global.h"
#include <iostream>
#include "PauseLayer.h"
#include "scene\GameScene.h"
#include "ui\CocosGUI.h"

using namespace ui;
USING_NS_CC;
using namespace std;

enum        // 地图元素类型 
{
	LAND,	// 地       0
	BRICK,	// 砖		1
	GRASS,  // 草		2
	WATER,  // 水		3
	GRID1,  // 铁1 左上	4
	GRID2,  // 铁2 右上	5
	GRID3,  // 铁3 左下	6
	GRID4,	// 铁4 右下	7
	HOME4,  // 大本营（完好）左上角	8
	HOME3,  // 大本营（完好）其余三角	9
	HOME2,  // 大本营（损坏）左上角 
	HOME1   // 大本营（损坏）其余三角 


};

class Stage :public LayerColor
{
public:
	CREATE_FUNC(Stage);
	virtual bool init();
	// 获取地图背景
	LayerColor * getBG() { return _bg; };
	/* 是否可打 */
	bool isCanHit(int row, int col);
	/* 是否可行走 */
	bool isCanWalk(int row, int col);
	/* 获取当前出现的敌人坦克的类型 */
	int getEnemyType() { return _type[_enemyID++]; }
	/* 获取当前出现的敌人坦克的id */
	int getCurEnemyId() { return _enemyID; }
	/* 获取地图元素的二维数组 */
	void getMap(int(*&map)[MAP_COL]) { map = _map; }
	/* 关卡胜利 */
	void win();
	/* 关卡失败 */
	void fail();
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 初始化红蓝进度条 */
	void initInfo();
	/* 更新地图元素 */
	void updateMapCell(int row, int col);
	/* GameScene */
	CC_SYNTHESIZE(GameScene *, gameScene, GameScene);
	//暂停层
	CC_SYNTHESIZE(PauseLayer *, pauseLayer, PauseLayer);
	/* getHP进度条 */
	Slider *getHPSlider() { return hpSlider; }
	/* get游戏进度条 */
	Slider *getProgressSlider() { return progressSlider; }
	/* 能否放大招 */
	bool changeIsKReady();
	/* 更新进度条,不包括MP */
	void sliderUpdate(float dt);
	/* 更新MP进度条*/
	void MPUpdate(float dt);

private:
	void onExit();
	/* 初始化地图 */
	void initMap();
	/* 创建地图元素 */
	void createMapCell(int row, int col, int type);
	/* 获取地图元素类型所对应的精灵图片的名字 */
	string getSpriteName(int type);


	int _id;						// 地图id(第一关为1)
	int _map[MAP_ROW][MAP_COL];		// 地图数组 
	int _type[ENEMY_NUM];			// 敌人坦克类型
	int _enemyID;					// 敌人坦克id（第一个出现的敌人坦克id为0） 
	LayerColor *_bg;				// 地图背景
	Slider *hpSlider;				// HP进度条
	Slider *mpSlider;				// MP进度条
	Slider *progressSlider;			// 进度
	Sprite *cursor;					// 游标
	float readyInterval;			// 冷却时间
	bool isReady;					// 大招是否准备好
	HeroType heroType;				// 英雄类型
	Animate *bigSkillAnimate;		//大招动画

};


//void Stage::setHomeWall(int newType)
//{
//	for (auto row = 23; row <= 25; row++)
//	{
//		for (auto col = 11; col <= 14; col++)
//		{
//			auto &type = _map[row][col];
//			if ((type & 0x0f) < HOME1) // 判断是否为大本营外围的墙（为了把大本营排除掉） 
//			{
//				type = newType;
//				updateMapCell(row, col);
//			}
//		}
//	}
//}