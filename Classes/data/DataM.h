#pragma once
#include "ExternData.h"
#include "cocos2d.h"
#include "Global.h"
#include "TankData.h"

USING_NS_CC;

enum HeroType
{
	TypeATK = 0,
	TypeDEF,
	TypeSPE,
};

class ExternData;
class DataM :public Layer
{
	// 此处破坏封装！！差评！！
	friend class ExternData;
	friend class TankData;
public:
	virtual bool init() override;
	static DataM *getInstance();
	CC_SYNTHESIZE(int, _id, _id); //自定义为-1
	CC_SYNTHESIZE(HeroType, hType, HType);
	//自定义敌方坦克难度 ，0到4
	CC_SYNTHESIZE(int, enemyDifficulty, EnemyDifficulty);
	CC_SYNTHESIZE(std::string, mapName, MapName);

	// 更新最大通关关卡
	bool updateMaxLevelCanPlayed();
	// 更新每关最大SP,关卡此时为DataM中的_id
	void updateLevelMaxScoreArray(int currentLevelScore);
	// 添加SP，负数为减
	void updateSP(int dSP);
	// 更新皮肤ID,更新哪个由hType决定,自动写入json
	void updateSkinId(int id);
	//得到皮肤ID
	int getSkinId(int id);
	// 此处没有封装，差评！！！
	int maxLevelCanPlayed;
	// 每一关的最大SP  此处json第一个数值写的是0，因为第一关的索引是1
	int levelMaxScoreArray[LEVEL_NUM + 1];
	// 加技能函数，给拐子用，返回SP的减少量
	int addSkill(int row, int col);
	// 获取当前所有的加点矩阵
	void getAllSPMatrix(int(*&SP)[5], int(*&SPMax)[5], int(*&SPNeed)[5], int(*&SPDepend)[5]);
	// 获取当前加点矩阵
	int(*getSPMartix())[5];
	// 获得当前皮肤ID，获得的类型由hType决定
	int getSkinId();
	// 获得当前SP总数，获得的类型由hType决定
	int getSP();

private:
	ExternData *externData;
	int ATKSP[5][5];		//攻击型坦克加点
	int ATKSPMax[5][5];		//攻击型坦克最大加点
	int ATKSPNeed[5][5];	//攻击型坦克加点需求
	int ATKSPDepend[5][5];	//攻击型坦克前置矩阵，四位二进制数，上右下左依次为1111.

	int DEFSP[5][5];		//防御型坦克加点
	int DEFSPMax[5][5];		//防御型坦克最大加点
	int DEFSPNeed[5][5];	//防御型坦克加点需求
	int DEFSPDepend[5][5];	//攻击型坦克前置矩阵，四位二进制数，上右下左依次为1111.

	int SPESP[5][5];		//速度型坦克加点
	int SPESPMax[5][5];		//速度型坦克最大加点
	int SPESPNeed[5][5];	//速度型坦克加点需求
	int SPESPDepend[5][5];	//攻击型坦克前置矩阵，四位二进制数，上右下左依次为1111.

	int ATKAddSkill(int row, int col);	//攻击型加点详细
	int DEFAddSkill(int row, int col);	//防御型加点详细
	int SPEAddSkill(int row, int col);	//速度型加点详细


	int ATKSkinId;			//攻击型皮肤ID
	int DEFSkinId;			//防御型皮肤ID
	int SPESkinId;			//速度型皮肤ID

	// 当前ATKSP
	int currentATKSP;
	// 当前DEFSP
	int currentDEFSP;
	// 当前SPESP
	int currentSPESP;
};