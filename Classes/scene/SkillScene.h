#pragma once
#include "cocos2d.h"
#include "data\SkillDetail.h"
#include "data\DataM.h"
#include "ui\UIScale9Sprite.h"

using namespace ui;
USING_NS_CC;

class SkillScene :public Layer
{
public:
	CREATE_FUNC(SkillScene);
	virtual bool init();

private:
	//上方光标
	Scale9Sprite *upSelectedRect;
	//下方光标
	Sprite *downSelectedRect;
	//技能页面下方粉色框框
	Sprite *rectBG;
	//星星总数标签
	Label *starAllNumLabel;
	//星星所需标签
	Label *starNeedNumLabel;
	//星星总数精灵
	Sprite *starAll;
	//星星所需精灵
	Sprite *starNeed;
	//技能描述,锚点在0
	Label *skillDiscribeLabel;  
	//技能名称，锚点在0
	Label *skillNameLabel;
	//星星总数
	int starAllNum;
	//星星所需
	int starNeedNum;
	//上方选项
	int option;
	//光标行数
	int row;
	//光标列数
	int col;
	//SP矩阵
	int(*SP)[5];
	//SPMax矩阵
	int(*SPMax)[5];
	//SPNeed矩阵
	int(*SPNeed)[5];
	//SP依赖矩阵
	int(*SPDepend)[5];

	// 是否在下方页面
	bool detailLayer;
	//当前的坦克类型
	HeroType heroType;

	//皮肤选项
	int skinId;
	//皮肤数量
	int skinNum;
	//皮肤总量
	int skinMax;

	DataM *dataM;
	SkillDetail *skillDetail;

	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
