/***********************************************

这里管理了游戏运行中坦克的基本数据，包括坦克的速、HP、攻击力等等，
此外，还通过SP矩阵计算当前坦克的属性

***********************************************/

#include "TankData.h"

static TankData * s_tankData = nullptr;

TankData::TankData():
dataM(DataM::getInstance())
{}

TankData *TankData::getInstance()
{
	if (s_tankData == nullptr)
	{
		s_tankData = new (std::nothrow) TankData();
		CCASSERT(s_tankData, "FATAL: Not enough memory");
	}
	return s_tankData;
}

int TankData::getHP()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 60 + dataM->ATKSP[1][0] * 20;
		break;
	case TypeDEF:
		return 150 + dataM->DEFSP[1][0] * 20;
		break;
	case TypeSPE:
		return 120 + dataM->SPESP[1][0] * 20;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

float TankData::getSPE()						//绝对坐标/秒
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 2 + dataM->ATKSP[2][0] * 0.5;
		break;
	case TypeDEF:
		return 3 + dataM->DEFSP[2][0] * 0.5;
		break;
	case TypeSPE:
		return 5 + dataM->SPESP[2][0] * 0.5;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}
int	TankData::getATK()
{
	auto heroType = DataM::getInstance()->getHType();
	int atk = 0;
	switch (heroType)
	{
	case TypeATK:
		//4(1)
		atk = 40 + dataM->ATKSP[0][0] * 10;
		break;
	case TypeDEF:
		//2(1)
		atk = 20 + dataM->DEFSP[0][0] * 10;
		break;
	case TypeSPE:
		//2(1)
		atk = 35 + dataM->SPESP[0][0] * 10;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
	return atk;
}

int TankData::getBulletNumMAX()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 1 + dataM->ATKSP[1][3] * 1 + dataM->ATKSP[2][3] * 1 + dataM->ATKSP[3][3] * 1;
		break;
	case TypeDEF:
		return 1 + dataM->DEFSP[0][3] * 1 + dataM->DEFSP[1][3] * 1;
		break;
	case TypeSPE:
		return 100;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

float TankData::getBulletSPE()					//绝对坐标/秒
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 7.0f + dataM->ATKSP[0][2] * 2.0f + dataM->ATKSP[1][2] * 2.0f + dataM->ATKSP[2][2] * 2.0f;
		break;
	case TypeDEF:
		return 7.0f + dataM->DEFSP[0][2] * 2.0f + dataM->DEFSP[1][2] * 2.0f;
		break;
	case TypeSPE:
		return 9.0f;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}


float TankData::getBulletDistance()				//绝对坐标
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 1000.0f;
		break;
	case TypeDEF:
		return 1000.0f;
		break;
	case TypeSPE:
		return 128.0f + dataM->SPESP[1][3] * 64.0f + dataM->SPESP[2][3] * 64.0f;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

bool TankData::isAOE()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		if (dataM->ATKSP[3][4] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case TypeDEF:
		return false;
		break;
	case TypeSPE:
		return false;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

float TankData::getAvoidProbability()			//0到1
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 0.0f;
		break;
	case TypeDEF:
		return 0.0f;
		break;
	case TypeSPE:
		return 0.0f + dataM->SPESP[1][4] * 0.15f + dataM->SPESP[2][4] * 0.15f + dataM->SPESP[3][4] * 0.15;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

int TankData::getDamageDiscount()			//伤害打折
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 0;
		break;
	case TypeDEF:
		return 0 + dataM->DEFSP[2][3] * 10;
		break;
	case TypeSPE:
		return 0;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

float TankData::getReadyInterval()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 30.0f - dataM->ATKSP[3][2] * 15.0f;
		break;
	case TypeDEF:
		return 50.0f;
		break;
	case TypeSPE:
		return 5.0f - dataM->SPESP[2][2] * 2.0f - (dataM->SPESP[0][2] * 1.0f) - (dataM->SPESP[1][2] * 1.0f);
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

bool TankData::isFireUp()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		if (dataM->ATKSP[2][4] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case TypeDEF:
		return false;
		break;
	case TypeSPE:
		return false;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

bool TankData::isRebirth()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return false;
		break;
	case TypeDEF:
		if (dataM->DEFSP[2][2] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case TypeSPE:
		return false;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

float TankData::getShieldTime()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 0.0f;
		break;
	case TypeDEF:
		if (dataM->DEFSP[3][3] != 0)
		{
			return 10.0f;
		}
		else
		{
			return 5.0f;
		}
		break;
	case TypeSPE:
		return 0.0f;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

int TankData::getJumpAbility()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 0;
		break;
	case TypeDEF:
		return 0;
		break;
	case TypeSPE:
		return 3 + dataM->SPESP[2][2] * 1;
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}

int TankData::getAtkInterval()
{
	auto heroType = DataM::getInstance()->getHType();
	switch (heroType)
	{
	case TypeATK:
		return 1000;  //不触发
		break;
	case TypeDEF:
		return 1000;  //不触发
		break;
	case TypeSPE:
		return  18 - (dataM->SPESP[0][2] * 6) - (dataM->SPESP[1][2] * 6);
		break;
	default:
		CCASSERT(NULL, "No Type of hero tank.");
		break;
	}
}