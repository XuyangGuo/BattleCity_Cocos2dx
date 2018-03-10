#include "Global.h"

bool g_keyUp = false;
bool g_keyRight = false;
bool g_keyDown = false;
bool g_keyLeft = false;
bool g_keySelect = false;
bool g_keyStart = false;
bool g_keyB = false;
bool g_keyA = false;
bool g_keyQ = false;
bool g_keyE = false;
bool g_keyR = false;
bool g_keyT = false;
bool g_keyY = false;
bool g_keyU = false;
bool g_keyI = false;
bool g_keyO = false;
bool g_keyP = false;
bool g_keyF = false;
bool g_keyG = false;
bool g_keyH = false;
bool g_keyL = false;
bool g_keyZ = false;
bool g_keyX = false;
bool g_keyC = false;
bool g_keyV = false;
bool g_key_B = false;
bool g_keyN = false;
bool g_keyM = false;
bool g_keyBACK = false;
bool g_keyCAPSLOCK = false;
bool g_keySPACE = false;
bool g_key0 = false;
bool g_key1 = false;
bool g_key2 = false;
bool g_key3 = false;
bool g_key4 = false;
bool g_key5 = false;
bool g_key6 = false;
bool g_key7 = false;
bool g_key8 = false;
bool g_key9 = false;

/* 获取地图某行某列所对应的坐标 */
Vec2 getPos(int row, int col)
{
	Vec2 pos;
	pos.x = col*CELL_WIDTH + MAP_ORIGIN.x + CELL_WIDTH / 2;
	pos.y = row*CELL_HEIGHT + MAP_ORIGIN.y + CELL_HEIGHT / 2;
	return pos;
}

int getColNumberFromPosition(float posX)
{
	return (int)((posX - MAP_ORIGIN.x) / 32);  
}

int getRowNumberFromPosition(float posY)
{
	return (int)((posY - MAP_ORIGIN.y) / 32);
}