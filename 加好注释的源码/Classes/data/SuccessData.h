/***********************************************

这是一个成就数据的管理系统，主要功能包括：
外部成就Json的读写，当前游戏即时成就的更新（
这主要通过update……接口来完成），以及成就完成的判定

***********************************************/

#pragma once
#include "json\rapidjson.h"
#include "json\writer.h"
#include "json\document.h"
#include "cocos2d.h"
#include "data\Global.h"
#include "data\DataM.h"

USING_NS_CC;
using namespace rapidjson;
class SuccessData 
{
public :
	static SuccessData *getInstance();
	//给旭阳的接口
	//更新持续时间
	void updateStayTime();
	//更新打破的砖块数
	void updateBrickNum();
	//更新打掉的坦克数目
	void updateHitTankNum();
	//更新用掉的子弹数目
	void updateBulletNum();
	//更新死亡次数
	void updateDeathTime();
	//更新家被打穿的次数
	void updateHomeBreakTime();
	//更新放大招的次数
	void updateBigSkillTime();
	//任意技能达到最大，已做最后关卡检测
	void updateIsSkillMax();
	//更新通关,已做最后关卡检测
	void updateIsAllLevel();
private:
	//打通所有成就
	void updateIsAllOpen();

public:

	//更新成就所获得的皮肤
	int updateSkin();
	//游戏结算时写入数据
	std::vector<char *> updateAlldata();

	//获得success数据-给拐子
	int getAllLevelProgress();  //打通所有关卡进度
	int getAllOpenProgress();	  //成就全开进度
	int getBigSkillTimeProgress();  //技能释放次数进度
	int getBrickNumProgress(); //破砖进度
	int getBulletNumProgress(); //子弹进度
	int getDeathTimeProgress();  //死亡次数进度
	int getHitTankNumProgress(); //歼敌进度
	int getHomeBreakTimeProgress(); //爆家进度
	int getSkillMaxProgress(); //最大技能情况进度
	int getStayTime();	//持续时间

	bool isAllLevelFinished() { return isAllLevel; }//是否通过所有的关卡
	bool isSkillMaxFinished() { return isSkillMax; }//任意技能满级
	bool isBrickNumFinished() { return isBrickNum; } //打破的砖块数
	bool isHitTankNumFinished() { return isHitTankNum; } //打掉的坦克数目
	bool isBulletNumFinished() { return isBulletNum; }//用掉的子弹数目
	bool isDeathTimeFinished() { return isDeathTime; }//死亡次数
	bool isHomeBreakTimeFinished() { return isHomeBreakTime; } // 家被打穿的次数
	bool isBigSkillTimeFinished() { return isBigSkillTime; }//放大招的次数
	bool isStayTimeFinished() {return isStayTime; }//待机时间
	bool isAllOpenFinished() {return isAllOpen; } //是否全部打通
										
private:
	bool init(); //从外部读取数据

	//判断是否得到皮肤
	int DEFSkin();
	int SPESkin();
	int ATKSkin();

	//Progress.json外部读写
	int brickNum; //打破的砖块数√
	int	hitTankNum; //打掉的坦克数目√
	int bulletNum;//用掉的子弹数目√
	int deathTime; //死亡次数√
	int homeBreakTime; // 家被打穿的次数√
	int bigSkillTime; //放大招的次数√

	//FinishedSuccess.json外部读写
	bool isAllLevel; //是否通过所有的关卡		Finished
	bool isSkillMax; //任意技能满级			Finished
	bool isBrickNum; //打破的砖块数			Finished
	bool isHitTankNum; //打掉的坦克数目		Finished
	bool isBulletNum;//用掉的子弹数目			Finished
	bool isDeathTime; //死亡次数				Finished
	bool isHomeBreakTime; // 家被打穿的次数	Finished
	bool isBigSkillTime; //放大招的次数		Finished
	bool isStayTime; //待机时间				Finished
	bool isAllOpen;  //是否全部打通			Finished

	void updateFinishedSuccess();

	//当前完成的成就，游戏胜利、失败、暂停返回时会被检查，清空
	std::vector<char *> currentFinished;


};