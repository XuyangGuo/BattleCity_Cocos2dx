#pragma once
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;

class SkillDetail :public Ref
{
public:
	static SkillDetail *getInstance();
	bool init();
	//得到技能名称，返回char*
	char *getSkillName(int row, int col);
	//得到技能描述，返回char*
	char *getSkillDescribe(int row, int col);
	//得到皮肤名称
	char *getSkinName();
private:
	int (*SP)[5];
};
