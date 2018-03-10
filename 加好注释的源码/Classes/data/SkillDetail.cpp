/***********************************************

主要存储英雄页面技能信息的详细描述

***********************************************/

#include "SkillDetail.h"
#include "ChineseFonts.h"

static SkillDetail* _skillDetail = nullptr;

SkillDetail *SkillDetail::getInstance()
{
	if (nullptr == _skillDetail)
	{
		_skillDetail = new (std::nothrow) SkillDetail();
		_skillDetail->init();
		CCASSERT(_skillDetail, "No memory to create _skillDetail");
	}
	return _skillDetail;
}

bool SkillDetail::init()
{
	return true;
}

//得到技能名称，返回char*
char *SkillDetail::getSkillName(int row, int col)
{
	SP = DataM::getInstance()->getSPMartix();
	char *nameInChinese = "";
	if (0 == col)
	{
		switch (row)
		{
		case 0:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("猛攻 Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //加满了
			{
				nameInChinese = "猛攻 Lv5 已加满";
			}
			break;
		case 1:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("重甲 Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //加满了
			{
				nameInChinese = "重甲 Lv5 已加满";
			}
			break;
		case 2:
			if (SP[row][col] < 5)
			{
				String *name = String::createWithFormat("疾驰 Lv%d", SP[row][col] + 1);
				nameInChinese = const_cast<char *>(name->getCString());
			}
			else  //加满了
			{
				nameInChinese = "疾驰 Lv5 已加满";
			}
			break;
		}
	}
	else  //col !=0
	{

		switch (DataM::getInstance()->getHType())
		{
		case TypeATK:
			if (2 == col)
			{
				if (row>=0 &&row <= 2)
					nameInChinese = "火力全开";
				else if (3 == row)
					nameInChinese = "维和者";
			}
			else if (3 == col)
			{
				if (row >= 1 && row <= 3)
					nameInChinese = "弹夹扩充";
			}
			else if (4 == col)
			{
				if (2 == row)
					nameInChinese = "熔火核心";
				else if (3 == row)
					nameInChinese = "随意开火";
			}
			break;
		case TypeDEF:
			if (2 == col)
			{
				if (row <= 1 && row >= 0)
					nameInChinese = "火力全开";
				else if (row == 2)
					nameInChinese = "钢铁意志";
			}
			else if (3 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "弹夹扩充";
				else if (2 == row)
					nameInChinese = "护甲柔化";
				else if (3 == row)
					nameInChinese = "无敌之师";
			}
			break;
		case TypeSPE:
			if (2 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "刃";
				else if(2 == row)
					nameInChinese = "乱";
			}
			else if (3 == col)
			{
				if (row <= 2 && row >= 1)
					nameInChinese = "缚";
			}
			else if (4 == col)
			{
				if (row <= 3 && row >= 1)
					nameInChinese = "闪";
			}
			break;
		default:
			break;
		}
	}
	return FontToUTF8(nameInChinese);
}

//得到技能描述，返回char*
char *SkillDetail::getSkillDescribe(int row, int col)
{
	char *nameInChinese = "";
	if (0 == col)
	{
		switch (row)
		{
		case 0:
				nameInChinese = "攻击力+10";
			break;
		case 1:
				nameInChinese = "防御力+10";
			break;
		case 2:
				nameInChinese = "速度+10";  //单位 px/20frame
			break;
		}
	}
	else  //col !=0
	{

		switch (DataM::getInstance()->getHType())
		{
		case TypeATK:
			if (2 == col)
			{
				if (row >= 0 && row <= 2)
					nameInChinese = "子弹速度+40";  //单位px/20frame
				else if (3 == row)
					nameInChinese = "终极技能：神枪手  冷却时间-15秒";
			}
			else if (3 == col)
			{
				if (row >= 1 && row <= 3)
					nameInChinese = "子弹数量存在上限+1";
			}
			else if (4 == col)
			{
				if (2 == row)
					nameInChinese = "攻击附带灼烧";
				else if (3 == row)
					nameInChinese = "普通攻击造成范围伤害，攻击至后两格";
			}
			break;
		case TypeDEF:
			if (2 == col)
			{
				if (row <= 1 && row >= 0)
					nameInChinese = "子弹速度+40";
				else if (row == 2)
					nameInChinese = "死亡后复活一次，获得100HP";
			}
			else if (3 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "子弹数量存在上限+1";
				else if (2 == row)
					nameInChinese = "被击伤害-10";
				else if (3 == row)
					nameInChinese = "终极技能：圣骑士  护盾时间+5秒";
			}
			break;
		case TypeSPE:
			if (2 == col)
			{
				if (row >= 0 && row <= 1)
					nameInChinese = "飞镖冷却时间-0.1秒，闪烁冷却时间-1.0秒";
				else if (2 == row)
					nameInChinese = "终极技能：幻  闪烁距离+1格，闪烁冷却时间-2秒";
			}
			else if (3 == col)
			{
				if (row <= 2 && row >= 1)
					nameInChinese = "飞镖攻击距离+1格";
			}
			else if (4 == col)
			{
				if (row <= 3 && row >= 1)
					nameInChinese = "增加15%回避率";
			}
			break;
		default:
			break;
		}
	}
	return FontToUTF8(nameInChinese);
}

char *SkillDetail::getSkinName()
{
	HeroType hTyoe = DataM::getInstance()->getHType();
	int skinId = DataM::getInstance()->getSkinId();
	char *nameInChinese;
	switch (hTyoe)
	{
	case TypeATK:
		if (0 == skinId)
		{
			nameInChinese = "攻击型皮肤";
		}
		else if (1 == skinId)
		{
			nameInChinese = "攻击型端午节皮肤";
		}
		else if (2 == skinId)
		{
			nameInChinese = "攻击型开发者调试专用箭头皮肤";
		}
		break;
	case TypeDEF:
		if (0 == skinId)
		{
			nameInChinese = "防御型皮肤";
		}
		else if (1 == skinId)
		{
			nameInChinese = "防御型万圣节皮肤";
		}
		else if (2 == skinId)
		{
			nameInChinese = "防御型开发者调试专用箭头皮肤";
		}
		break;
	case TypeSPE:
		if (0 == skinId)
		{
			nameInChinese = "速度型皮肤";
		}
		else if (1 == skinId)
		{
			nameInChinese = "速度型圣诞节皮肤";
		}
		else if (2 == skinId)
		{
			nameInChinese = "速度型开发者调试专用箭头皮肤";
		}
		break;
	default:
		break;
	}
	return FontToUTF8(nameInChinese);
}