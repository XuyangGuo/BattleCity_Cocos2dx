/***********************************************

主要存储全局变量，例如键盘状态，关卡数量，
每一关地方坦克数量，地图长宽等等

***********************************************/

#pragma once

#include "cocos2d.h"
USING_NS_CC;


const auto SCREEN_WIDTH = 1024;                         // 屏幕宽度
const auto SCREEN_HEIGHT = 768;							// 屏幕高度
const auto SCREEN_CX = SCREEN_WIDTH / 2;				// 屏幕高度的一般
const auto SCREEN_CY = SCREEN_HEIGHT / 2;				// 屏幕宽度的一般
const auto CELL_WIDTH = 32;								// 地图元素的宽 
const auto CELL_HEIGHT = 32;							// 地图元素的高
const auto MAP_ROW = 18;								// 地图行数 
const auto MAP_COL = 28;								// 地图列数 
const auto MAP_WIDTH = MAP_COL*CELL_WIDTH;				// 地图宽度 
const auto MAP_HEIGHT = MAP_ROW*CELL_HEIGHT;			// 地图高度
const Vec2 MAP_ORIGIN(64, 128);							// 地图左下原点坐标
const Vec2 MAP_RIGHTUP(960, 704);						// 地图右上角顶点坐标
const auto FIRSTCOL = 0;								// 第一列是0
const auto FIRSTROW = 0;								// 第一行是0
const auto LEVEL_NUM = 15;								// 关卡数量	第一关是1
const auto ENEMY_NUM = 30;								// 关卡坦克数量
const auto LEFT_EAGE = MAP_ORIGIN.x;					// 左边界
const auto RIGHT_EAGE = MAP_RIGHTUP.x;					// 右边界
const auto TOP_EAGE = MAP_RIGHTUP.y;					// 上边界
const auto BOTTOM_EAGE = MAP_ORIGIN.y;					// 下边界

/**********

小方块的坐标以左下角为准

**************/

enum Direction	// 方向 
{
	UP = 1,		// 上 
	RIGHT,		// 右 
	DOWN,		// 下 
	LEFT		// 左 
};

// 键盘按键
extern bool g_keyUp;
extern bool g_keyRight;
extern bool g_keyDown;
extern bool g_keyLeft;
extern bool g_keySelect;
extern bool g_keyStart;
extern bool g_keyB;
extern bool g_keyA;
extern bool g_keyQ;
extern bool g_keyE;
extern bool g_keyR;
extern bool g_keyT;
extern bool g_keyY;
extern bool g_keyU;
extern bool g_keyI;
extern bool g_keyO;
extern bool g_keyP;
extern bool g_keyF;
extern bool g_keyG;
extern bool g_keyH;
extern bool g_keyL;
extern bool g_keyZ;
extern bool g_keyX;
extern bool g_keyC;
extern bool g_keyV;
extern bool g_key_B;
extern bool g_keyN;
extern bool g_keyM;
extern bool g_keyBACK;
extern bool g_keyCAPSLOCK;
extern bool g_keySPACE;
extern bool g_key0;
extern bool g_key1;
extern bool g_key2;
extern bool g_key3;
extern bool g_key4;
extern bool g_key5;
extern bool g_key6;
extern bool g_key7;
extern bool g_key8;
extern bool g_key9;

/* 通过地图的行列计算出坐标 */
extern Vec2 getPos(int row, int col);
//通过绝对坐标获得行数
//四格中心点归属右上方格
extern int getColNumberFromPosition(float posX); 
//通过绝对坐标获得列数
//四格中心点归属右上方格
extern int getRowNumberFromPosition(float posY);  