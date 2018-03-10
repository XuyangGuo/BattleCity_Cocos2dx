/***********************************************

主要存取外部Json文件，
作为游戏内部数据和外部文件数据对接的桥梁

***********************************************/

#pragma once
#include "json\rapidjson.h"
#include "json\writer.h"
#include "json\document.h"
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;
using namespace rapidjson;
class DataM;
class ExternData
{
public:
	// 此处破坏封装！！差评！！
	friend DataM;
	// 刷新梯度加点
	void changeToGradSP(int(*SPNeed)[5], int(*SP)[5]);

private:

	static ExternData *getInstance();

	bool init();		// 从外部读取数据

	// 读SPNeed，注意，读哪个由hType决定！！
	void readSPNeed();

	//写入最大通关数到文件
	void writeMaxLevelCanPlayed();

	//写入LevelMaxScoreArray数到文件
	void writeLevelMaxScoreArray();

	//写入SP数到文件，3个都更新
	void writeSP();

	////写入SPMax到文件,注意，写哪个由hType决定！！
	//void writeSPMax();

	//写入SP到文件,注意，写哪个由hType决定！！
	void writeSPSkill();

	//写入SkinID到文件,3个都更新
	void writeSkinID();

	DataM *dataM;

};