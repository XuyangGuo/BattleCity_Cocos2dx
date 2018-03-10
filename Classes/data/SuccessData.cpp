#include "SuccessData.h"
#include "DataM.h"
#include "data\StayTime.h"
#include "ChineseFonts.h"

static SuccessData * s_successData = nullptr;

SuccessData *SuccessData::getInstance()
{
	if (!s_successData)
	{
		s_successData = new SuccessData();
		s_successData->init();
		assert(s_successData, "No enough memory of externData.");
	}
	return s_successData;
}

bool SuccessData::init()
{
	Document progress;
	std::string progressString = FileUtils::getInstance()->getStringFromFile("Progress.json");
	progress.Parse<kParseDefaultFlags>(progressString.c_str());

	//读取大招释放次数
	bigSkillTime = progress["BigSkillTime"].GetInt();
	// 读取打破的砖块数
	brickNum = progress["BrickNum"].GetInt();
	//读取发射子弹总数
	bulletNum = progress["BulletNum"].GetInt();
	//读取死亡次数
	deathTime = progress["DeathTime"].GetInt();
	//读取击破坦克数量
	hitTankNum = progress["HitTankNum"].GetInt();
	//读取家被打爆次数
	homeBreakTime = progress["HomeBreakTime"].GetInt();

	Document finishedSuccess;
	std::string finishedSuccessString = FileUtils::getInstance()->getStringFromFile("FinishedSuccess.json");
	finishedSuccess.Parse<kParseDefaultFlags>(finishedSuccessString.c_str());

	isAllLevel = finishedSuccess["AllLevel"].GetBool();
	isSkillMax = finishedSuccess["SkillMax"].GetBool();
	isBrickNum = finishedSuccess["BrickNum"].GetBool();
	isHitTankNum = finishedSuccess["HitTankNum"].GetBool();
	isBulletNum = finishedSuccess["BulletNum"].GetBool();
	isDeathTime = finishedSuccess["DeathTime"].GetBool();
	isHomeBreakTime = finishedSuccess["HomeBreakTime"].GetBool();
	isBigSkillTime = finishedSuccess["BigSkillTime"].GetBool();
	isStayTime = finishedSuccess["StayTime"].GetBool();
	isAllOpen = finishedSuccess["AllOpen"].GetBool();

	//currentFinished.clear();

	return true;
}

//给旭阳的函数
void SuccessData::updateBrickNum()
{
	brickNum++;

}

void SuccessData::updateHitTankNum() 
{
	hitTankNum++;
}

void SuccessData::updateBulletNum() 
{
	bulletNum++;
}

void SuccessData::updateDeathTime() 
{
	deathTime++;
}

void SuccessData::updateHomeBreakTime() 
{
	homeBreakTime++;
}

void SuccessData::updateBigSkillTime() 
{
	bigSkillTime++;
}

void SuccessData::updateStayTime()
{
	if (!isStayTime)
	{
		isStayTime = true;
		char * temp = (FontToUTF8("在洗澡呢 达成!"));
		currentFinished.push_back(temp);
		//时间到了写入json
		updateAlldata();
	}
}

void SuccessData::updateIsSkillMax()
{
	if (!isSkillMax)
	{
		int(*SP)[5] = DataM::getInstance()->getSPMartix();
		if (SP[0][0] == 5 || SP[1][0] == 5 || SP[2][0] == 5)
		{
			isSkillMax = true;
			char * temp = (FontToUTF8("大师 达成!"));
			currentFinished.push_back(temp);
		}
	}
}

void SuccessData::updateIsAllLevel()
{
	if (!isAllLevel && DataM::getInstance()->get_id() == 15)
	{
		isAllLevel = true;
		char * temp = (FontToUTF8("独孤求败 达成!"));
		currentFinished.push_back(temp);
	}
}

void SuccessData::updateIsAllOpen()
{
	if (!isAllOpen)
	{
		isAllOpen = true;
		char * temp = (FontToUTF8("老司机 达成!"));
		currentFinished.push_back(temp);
	}
}


//总的结算成就
std::vector<char *> SuccessData::updateAlldata()
{
	//准备返回当前完成的成就
	updateFinishedSuccess();

	//进度
	Document progress;
	progress.SetObject();
	rapidjson::Document::AllocatorType &allocator1 = progress.GetAllocator();

	progress.AddMember("BigSkillTime", bigSkillTime, allocator1);
	progress.AddMember("BrickNum", brickNum, allocator1);
	progress.AddMember("BulletNum", bulletNum, allocator1);
	progress.AddMember("DeathTime", deathTime, allocator1);
	progress.AddMember("HitTankNum", hitTankNum, allocator1);
	progress.AddMember("HomeBreakTime", homeBreakTime, allocator1);

	StringBuffer buffer1;
	rapidjson::Writer<StringBuffer> writer1(buffer1);
	progress.Accept(writer1);
	FILE* file1 = fopen("externData/successData/Progress.json", "wb");
	if (file1)
	{
		fputs(buffer1.GetString(), file1);
		fclose(file1);
	}

	//完成所有成就
	if (isAllLevel && isSkillMax && isBrickNum && isHitTankNum && isBulletNum && isDeathTime && isHomeBreakTime && isBigSkillTime && isStayTime)
	{
		updateIsAllOpen();
	}

	//完成情况
	Document finishedSuccess;
	finishedSuccess.SetObject();
	rapidjson::Document::AllocatorType &allocator2 = finishedSuccess.GetAllocator();

	finishedSuccess.AddMember("AllLevel", isAllLevel, allocator2);
	finishedSuccess.AddMember("AllOpen", isAllOpen, allocator2);
	finishedSuccess.AddMember("BigSkillTime", isBigSkillTime, allocator2);
	finishedSuccess.AddMember("BrickNum", isBrickNum, allocator2);
	finishedSuccess.AddMember("BulletNum", isBulletNum, allocator2);
	finishedSuccess.AddMember("DeathTime", isDeathTime, allocator2);
	finishedSuccess.AddMember("HitTankNum", isHitTankNum, allocator2);
	finishedSuccess.AddMember("HomeBreakTime", isHomeBreakTime, allocator2);
	finishedSuccess.AddMember("SkillMax", isSkillMax, allocator2);
	finishedSuccess.AddMember("StayTime", isStayTime, allocator2);

	StringBuffer buffer2;
	rapidjson::Writer<StringBuffer> writer2(buffer2);
	finishedSuccess.Accept(writer2);
	FILE* file2 = fopen("externData/successData/FinishedSuccess.json", "wb");
	if (file2)
	{
		fputs(buffer2.GetString(), file2);
		fclose(file2);
	}

	//返回一个Vector，用来显示完成了啥啥啥
	std::vector<char *> tempCurrentFinished(currentFinished);
	currentFinished.clear();

	return tempCurrentFinished;
}

void SuccessData::updateFinishedSuccess()
{
	//1
	if (brickNum >= 1000 && isBrickNum == false)
	{
		isBrickNum = true;
		char * temp(FontToUTF8("搬砖工 达成!"));
		currentFinished.push_back(temp);
	}
	//2
	if (hitTankNum >= 300 && isHitTankNum == false)
	{
		isHitTankNum = true;
		char * temp = (FontToUTF8("杀人如麻 达成!"));
		currentFinished.push_back(temp);
	}
	//3
	if (bulletNum >= 2000 && isBulletNum == false)
	{
		isBulletNum = true;
		char * temp = (FontToUTF8("神枪手 达成!"));
		currentFinished.push_back(temp);
	}
	//4
	if (deathTime >= 15 && isDeathTime == false)
	{
		isDeathTime = true;
		char * temp = (FontToUTF8("死神来了 达成!"));
		currentFinished.push_back(temp);
	}
	//5
	if (homeBreakTime >= 20 && isHomeBreakTime == false)
	{
		isHomeBreakTime = true;
		char * temp = (FontToUTF8("隔壁老王 达成!"));
		currentFinished.push_back(temp);
	}
	//6
	if (bigSkillTime >= 30 && isBigSkillTime == false)
	{
		isBigSkillTime = true;
		char *temp = (FontToUTF8("洪荒之力 达成!"));
		currentFinished.push_back(temp);
	}
//另外四个写在上面的各自的update中
}

//判断是否获得皮肤
int SuccessData::DEFSkin() {
	int skinNum = 1;
	if (isBrickNum && isHitTankNum && isBigSkillTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::SPESkin() {
	int skinNum = 1;
	if (isHomeBreakTime && isSkillMax && isDeathTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::ATKSkin() 
{
	int skinNum = 1;
	if (isAllLevel  && isBulletNum && isStayTime)
		skinNum++;
	if (isAllOpen)
		skinNum++;
	return skinNum;
}

int SuccessData::updateSkin()
{
	int skinNum;
	switch (DataM::getInstance()->getHType())
	{
	case TypeDEF:
		skinNum = DEFSkin();
		break;
	case TypeATK:
		skinNum = ATKSkin();
		break;
	case TypeSPE:
		skinNum = SPESkin();
		break;
	}
	return skinNum;
}

//获得success数据-给拐子

//打通所有关卡进度
int SuccessData::getAllLevelProgress()
{
	return isAllLevel ? (LEVEL_NUM) : (DataM::getInstance()->maxLevelCanPlayed - 1); 
}  
  //成就全开进度
int SuccessData::getAllOpenProgress()
{
	return (int)isAllLevel
		+ (int)isSkillMax
		+ (int)isBrickNum
		+ (int)isHitTankNum
		+ (int)isBulletNum
		+ (int)isDeathTime
		+ (int)isHomeBreakTime
		+ (int)isBigSkillTime
		+ (int)isStayTime
		+ (int)isAllOpen;
}	 

//技能释放次数进度
int SuccessData::getBigSkillTimeProgress() 
{
	return bigSkillTime; 
}  

//破砖进度
int SuccessData::getBrickNumProgress()
{ 
	return brickNum; 
}  

//子弹进度
int SuccessData::getBulletNumProgress() 
{
	return bulletNum; 
} 

//死亡次数进度
int SuccessData::getDeathTimeProgress()
{
	return deathTime; 
}  

//歼敌进度
int SuccessData::getHitTankNumProgress()
{
	return hitTankNum;
}  

//爆家进度
int SuccessData::getHomeBreakTimeProgress()
{ 
	return homeBreakTime;
} 

//最大技能情况进度
int SuccessData::getSkillMaxProgress()
{

	DataM *dataM = DataM::getInstance();
	int currentTypeNum = (int)(dataM->getHType());
	int maxSkillLearned = 0;
	//循环结束，英雄类型不变
	for (int i = 2; i >= 0; --i)
	{
		dataM->setHType((HeroType)((currentTypeNum + i) % 3));
		int(*SPMartix)[5] = dataM->getSPMartix();
		for (int j = 0; j < 3; j++)
		{
			maxSkillLearned = (SPMartix[j][0]>maxSkillLearned) ? SPMartix[j][0] : maxSkillLearned;
		}
	}
	return maxSkillLearned;
} 

//持续时间
int SuccessData::getStayTime() 
{ 
	return StayTime::getStayTime(); 
}