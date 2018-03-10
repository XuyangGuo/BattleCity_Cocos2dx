/***********************************************

主要存取SP、关卡信息、皮肤ID、英雄类型，
是后台数据管理的场所，游戏前端数据和外部数据的连接的桥梁

***********************************************/


#include "dataM.h"

static DataM* s_dataM = nullptr;

DataM *DataM::getInstance()
{
	if (!s_dataM)
	{
		s_dataM = new (std::nothrow) DataM();
		CCASSERT(s_dataM, "FATAL: Not enough memory");
		s_dataM->init();
	}
	return s_dataM;
}

bool DataM::init()
{
	// 第一次执行时，数据会被初始化 在ExternData::init()中
	externData = ExternData::getInstance();
	return true;
}
//更新最大关卡
bool DataM::updateMaxLevelCanPlayed()
{
	if (maxLevelCanPlayed == _id)
	{
		maxLevelCanPlayed++;
		externData->writeMaxLevelCanPlayed();
		return true;
	}
	return false;
}
//更新最大分数
void DataM::updateLevelMaxScoreArray(int currentLevelScore)
{
	if (currentLevelScore > levelMaxScoreArray[_id])
	{
		updateSP(currentLevelScore - levelMaxScoreArray[_id]);
		levelMaxScoreArray[_id] = currentLevelScore;
		externData->writeLevelMaxScoreArray();
	}
}
//更新SP
void DataM::updateSP(int dSP)
{
	currentATKSP += dSP;
	currentDEFSP += dSP;
	currentSPESP += dSP;
	externData->writeSP();
}

// 返回的是SP的减少量,返回值为0时没有音效，没用动画，请自己添加
int DataM::addSkill(int row, int col)
{
	int spDecrement = 0;
	switch (hType)
	{
	case TypeATK:
		spDecrement = ATKAddSkill(row, col);
		break;
	case TypeDEF:
		spDecrement = DEFAddSkill(row, col);
		break;
	case TypeSPE:
		spDecrement = SPEAddSkill(row, col);
		break;
	default:
		CCASSERT(false, "No exist Type!!");
		break;
	}
	externData->readSPNeed();	//类型自动考虑,更新剩余点数
	externData->writeSPSkill();  //类型由hType决定
	externData->writeSP();		//更新当前三者SP
	return spDecrement;
}
//ATK类型坦克加点
int DataM::ATKAddSkill(int row, int col)
{
	if (ATKSPMax[row][col] > ATKSP[row][col])
	{
		int spDecrement = ATKSPNeed[row][col];
		ATKSP[row][col]++;
		currentATKSP = currentATKSP - spDecrement;
		//加动画，加音效
		return spDecrement;
	}
	else
	{
		return 0;
	}
}
//DEF类型坦克加点
int DataM::DEFAddSkill(int row, int col)
{
	if (DEFSPMax[row][col] > DEFSP[row][col])
	{
		int spDecrement = DEFSPNeed[row][col];
		DEFSP[row][col]++;
		currentDEFSP = currentDEFSP - spDecrement;
		//加动画，加音效
		return spDecrement;
	}
	else
	{
		return 0;
	}
}
//SPE类型坦克加点
int DataM::SPEAddSkill(int row, int col)
{

	if (SPESPMax[row][col] > SPESP[row][col])
	{
		int spDecrement = SPESPNeed[row][col];
		SPESP[row][col]++;
		currentSPESP = currentSPESP - spDecrement;
		//加动画，加音效
		return spDecrement;
	}
	else
	{
		return 0;
	}
}

void DataM::getAllSPMatrix(int(*&SP)[5], int(*&SPMax)[5], int(*&SPNeed)[5], int(*&SPDepend)[5])
{
	switch (hType)
	{
	case TypeATK:
		SP = ATKSP;
		SPMax = ATKSPMax;
		SPNeed = ATKSPNeed;
		SPDepend = ATKSPDepend;
		break;

	case TypeDEF:
		SP = DEFSP;
		SPMax = DEFSPMax;
		SPNeed = DEFSPNeed;
		SPDepend = DEFSPDepend;
		break;

	case TypeSPE:
		SP = SPESP;
		SPMax = SPESPMax;
		SPNeed = SPESPNeed;
		SPDepend = SPESPDepend;
		break;
	}
}
//得到各个类型坦克的id
int DataM::getSkinId()
{
	switch (hType)
	{
	case TypeATK:
		return ATKSkinId;
		break;
	case TypeDEF:
		return DEFSkinId;
		break;
	case TypeSPE:
		return SPESkinId;
		break;
	}
}

void DataM::updateSkinId(int id)
{
	switch (hType)
	{
	case TypeATK:
		ATKSkinId = id;
		break;
	case TypeDEF:
		DEFSkinId = id;
		break;
	case TypeSPE:
		SPESkinId = id;
		break;
	}
	externData->writeSkinID();
	return;
}

int DataM::getSP()
{
	switch (hType)
	{
	case TypeATK:
		return currentATKSP;
		break;
	case TypeDEF:
		return currentDEFSP;
		break;
	case TypeSPE:
		return currentSPESP;
		break;
	}
}

int(*DataM::getSPMartix())[5]
{
	switch (hType)
	{
	case TypeATK:
		return ATKSP;
		break;
	case TypeDEF:
		return DEFSP;
		break;
	case TypeSPE:
		return SPESP;
		break;
	}
}

int DataM::getSkinId(int id)
{
	switch (hType)
	{
	case TypeATK:
		return ATKSkinId;
		break;
	case TypeDEF:
		return DEFSkinId;
		break;
	case TypeSPE:
		return SPESkinId;
		break;
	default:
		break;
	}
}