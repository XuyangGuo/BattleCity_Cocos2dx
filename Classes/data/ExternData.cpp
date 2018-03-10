#include "ExternData.h"
#include "Global.h"

static ExternData * s_externData = nullptr;

ExternData *ExternData::getInstance()
{
	if (!s_externData)
	{
		s_externData = new ExternData();
		s_externData->init();
		assert(s_externData, "No enough memory of externData.");
	}
	return s_externData;
}

bool ExternData::init()
{
	dataM = DataM::getInstance();

	// 读取最大关卡信息
	Document maxLevelDoc;
	std::string maxLevelString = FileUtils::getInstance()->getStringFromFile("MaxLevelCanPlayed.json");
	maxLevelDoc.Parse<kParseDefaultFlags>(maxLevelString.c_str());
	rapidjson::Value &maxLevel = maxLevelDoc["MaxLevelCanPlayed"];
	if (maxLevel.IsInt())
	{
		dataM->maxLevelCanPlayed = maxLevel.GetInt();
	}

	//剩余SP
	Document spDoc;
	std::string spString = FileUtils::getInstance()->getStringFromFile("SP.json");
	spDoc.Parse<kParseDefaultFlags>(spString.c_str());
	//剩余ATKSP
	rapidjson::Value &currentATKSP = spDoc["CurrentATKSP"];
	if (currentATKSP.IsInt())
	{
		dataM->currentATKSP = currentATKSP.GetInt();
	}
	//剩余DEFSP
	rapidjson::Value &currentDEFSP = spDoc["CurrentDEFSP"];
	if (currentDEFSP.IsInt())
	{
		dataM->currentDEFSP = currentDEFSP.GetInt();
	}
	//剩余DEFSP
	rapidjson::Value &currentSPESP = spDoc["CurrentSPESP"];
	if (currentSPESP.IsInt())
	{
		dataM->currentSPESP = currentSPESP.GetInt();
	}


	//每关获得星星数量
	Document levelMaxScoreDoc;
	std::string levelMaxScoreString = FileUtils::getInstance()->getStringFromFile("LevelMaxScore.json");
	levelMaxScoreDoc.Parse<kParseDefaultFlags>(levelMaxScoreString.c_str());
	rapidjson::Value &levelMaxScore = levelMaxScoreDoc["LevelMaxScore"];
	for (int i = 0; i < LEVEL_NUM + 1; ++i)
	{
		dataM->levelMaxScoreArray[i] = levelMaxScore[i].GetInt();
	}

	// 攻击型坦克SP最大值 矩阵
	Document ATKSPMax;
	std::string ATKSPMaxString = FileUtils::getInstance()->getStringFromFile("ATKSPMax.json");
	ATKSPMax.Parse<kParseDefaultFlags>(ATKSPMaxString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->ATKSPMax[i][j] = ATKSPMax[i][j].GetInt();
		}
	}

	// 攻击型坦克SP 矩阵
	Document ATKSP;
	std::string ATKSPString = FileUtils::getInstance()->getStringFromFile("ATKSP.json");
	ATKSP.Parse<kParseDefaultFlags>(ATKSPString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->ATKSP[i][j] = ATKSP[i][j].GetInt();
		}
	}

	// 攻击型坦克SP 依赖矩阵
	Document ATKSPDepend;
	std::string ATKSPDependString = FileUtils::getInstance()->getStringFromFile("ATKSPDepend.json");
	ATKSPDepend.Parse<kParseDefaultFlags>(ATKSPDependString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->ATKSPDepend[i][j] = ATKSPDepend[i][j].GetInt();
		}
	}

	// 防御型坦克的SP最大值 矩阵
	Document DEFSPMax;
	std::string DEFSPMaxString = FileUtils::getInstance()->getStringFromFile("DEFSPMax.json");
	DEFSPMax.Parse<kParseDefaultFlags>(DEFSPMaxString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->DEFSPMax[i][j] = DEFSPMax[i][j].GetInt();
		}
	}

	// 防御型坦克SP 矩阵
	Document DEFSP;
	std::string DEFSPString = FileUtils::getInstance()->getStringFromFile("DEFSP.json");
	DEFSP.Parse<kParseDefaultFlags>(DEFSPString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->DEFSP[i][j] = DEFSP[i][j].GetInt();
		}
	}

	// 防御型坦克SP 依赖矩阵
	Document DEFSPDepend;
	std::string DEFSPDependString = FileUtils::getInstance()->getStringFromFile("DEFSPDepend.json");
	DEFSPDepend.Parse<kParseDefaultFlags>(DEFSPDependString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->DEFSPDepend[i][j] = DEFSPDepend[i][j].GetInt();
		}
	}

	// 速度型坦克的SP最大值 矩阵
	Document SPESPMax;
	std::string SPESPMaxString = FileUtils::getInstance()->getStringFromFile("SPESPMax.json");
	SPESPMax.Parse<kParseDefaultFlags>(SPESPMaxString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->SPESPMax[i][j] = SPESPMax[i][j].GetInt();
		}
	}

	// 速度型坦克SP 矩阵
	Document SPESP;
	std::string SPESPString = FileUtils::getInstance()->getStringFromFile("SPESP.json");
	SPESP.Parse<kParseDefaultFlags>(SPESPString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->SPESP[i][j] = SPESP[i][j].GetInt();
		}
	}

	// 速度型坦克SP 依赖矩阵
	Document SPESPDepend;
	std::string SPESPDependString = FileUtils::getInstance()->getStringFromFile("SPESPDepend.json");
	SPESPDepend.Parse<kParseDefaultFlags>(SPESPDependString.c_str());
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			dataM->SPESPDepend[i][j] = SPESPDepend[i][j].GetInt();
		}
	}

	// SPNeed矩阵
	dataM->hType = TypeATK;
	readSPNeed();
	dataM->hType = TypeDEF;
	readSPNeed();
	dataM->hType = TypeSPE;
	readSPNeed();
	dataM->hType = TypeATK;

	// 读取皮肤信息
	Document skinId;
	std::string skinIdString = FileUtils::getInstance()->getStringFromFile("SkinId.json");
	skinId.Parse<kParseDefaultFlags>(skinIdString.c_str());
	dataM->ATKSkinId = skinId["ATKSkinId"].GetInt();
	dataM->DEFSkinId = skinId["DEFSkinId"].GetInt();
	dataM->SPESkinId = skinId["SPESkinId"].GetInt();

	return true;
}

void ExternData::readSPNeed()
{
	Document SPNeed;
	std::string SPNeedString;
	switch (dataM->hType)
	{
	case TypeATK:
		SPNeedString = FileUtils::getInstance()->getStringFromFile("ATKSPNeedOrigin.json");
		SPNeed.Parse<kParseDefaultFlags>(SPNeedString.c_str());
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				dataM->ATKSPNeed[i][j] = SPNeed[i][j].GetInt();
			}
		}
		changeToGradSP(dataM->ATKSPNeed,dataM->ATKSP);
		break;

	case TypeDEF:
		SPNeedString = FileUtils::getInstance()->getStringFromFile("DEFSPNeedOrigin.json");
		SPNeed.Parse<kParseDefaultFlags>(SPNeedString.c_str());
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				dataM->DEFSPNeed[i][j] = SPNeed[i][j].GetInt();
			}
		}
		changeToGradSP(dataM->DEFSPNeed, dataM->DEFSP);
		break;

	case TypeSPE:
		SPNeedString = FileUtils::getInstance()->getStringFromFile("SPESPNeedOrigin.json");
		SPNeed.Parse<kParseDefaultFlags>(SPNeedString.c_str());
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				dataM->SPESPNeed[i][j] = SPNeed[i][j].GetInt();
			}
		}
		changeToGradSP(dataM->SPESPNeed, dataM->SPESP);
		break;
	}
}

void ExternData::changeToGradSP(int (*SPNeed)[5], int(*SP)[5])
{
	for (int i = 0; i < 3; ++i)
	{
		if (SP[i][0] >= 2)
		{
			SPNeed[i][0]++;
		}
	}
}

void ExternData::writeMaxLevelCanPlayed()
{
	Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
	doc.AddMember("MaxLevelCanPlayed", dataM->maxLevelCanPlayed, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	FILE* file = fopen("externData/MaxLevelCanPlayed.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}

	//// save as a json
	//Document doc;
	//doc.SetObject();
	//rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
	//rapidjson::Value array(rapidjson::kArrayType);
	//rapidjson::Value object(rapidjson::kObjectType);

	//object.AddMember("inttag", 1, allocator);
	//object.AddMember("doubletag", 1.0, allocator);
	//object.AddMember("booltage", true, allocator);
	//object.AddMember("hellotag", "helloWorld", allocator);

	//array.PushBack(object, allocator);

	//doc.AddMember("json", "json string", allocator);
	//doc.AddMember("array", array, allocator);

	//// save in a file
	//StringBuffer buffer;
	//rapidjson::Writer<StringBuffer> writer(buffer);
	//doc.Accept(writer);

	//FILE* file = fopen("myhero1.json", "wb");
	//if (file)
	//{
	//	fputs(buffer.GetString(), file);
	//	fclose(file);
	//}
	//// end

}

void ExternData::writeSP()
{
	Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

	doc.AddMember("CurrentATKSP", dataM->currentATKSP, allocator);
	doc.AddMember("CurrentDEFSP", dataM->currentDEFSP, allocator);
	doc.AddMember("CurrentSPESP", dataM->currentSPESP, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	FILE* file = fopen("externData/SP.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}

void ExternData::writeLevelMaxScoreArray()
{
	// save as a json
	Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

	rapidjson::Value levelMaxScoreArray(rapidjson::kArrayType);

	for (int i = 0; i < LEVEL_NUM + 1; ++i)
	{
		levelMaxScoreArray.PushBack(dataM->levelMaxScoreArray[i], allocator);
	}

	doc.AddMember("LevelMaxScore", levelMaxScoreArray, allocator);

	// save in a file
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	FILE* file = fopen("externData/LevelMaxScore.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	// end
}
//
//void ExternData::writeSPMax()
//{
//	//save as a json
//	Document doc;
//	doc.SetArray();
//	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
//
//	std::string failName;
//	switch (dataM->getHType())
//	{
//	case TypeATK:
//		// SPMax是指矩阵中的一个点
//		for (int i = 0; i < 5; ++i)
//		{
//			rapidjson::Value SPMax(rapidjson::kArrayType);
//			SPMax.Clear();
//			for (int j = 0; j < 5; ++j)
//			{
//				SPMax.PushBack(dataM->ATKSPMax[i][j], allocator);
//			}
//			doc.PushBack(SPMax, allocator);
//		}
//		failName = "externData/Skill/ATKSPMax.json";
//		break;
//
//	case TypeDEF:
//		// SPMax是指矩阵中的一个点
//		for (int i = 0; i < 5; ++i)
//		{
//			rapidjson::Value SPMax(rapidjson::kArrayType);
//			SPMax.Clear();
//			for (int j = 0; j < 5; ++j)
//			{
//				SPMax.PushBack(dataM->DEFSPMax[i][j], allocator);
//			}
//			doc.PushBack(SPMax, allocator);
//		}
//		failName = "externData/Skill/DEFSPMax.json";
//		break;
//
//	case TypeSPE:
//		// SPMax是指矩阵中的一个点
//		for (int i = 0; i < 5; ++i)
//		{
//			rapidjson::Value SPMax(rapidjson::kArrayType);
//			SPMax.Clear();
//			for (int j = 0; j < 5; ++j)
//			{
//				SPMax.PushBack(dataM->SPESPMax[i][j], allocator);
//			}
//			doc.PushBack(SPMax, allocator);
//		}
//		failName = "externData/Skill/SPESPMax.json";
//		break;
//	default:
//		break;
//	}
//
//	// save in a file
//	StringBuffer buffer;
//	rapidjson::Writer<StringBuffer> writer(buffer);
//	doc.Accept(writer);
//
//	FILE* file = fopen(failName.c_str(), "wb");
//	if (file)
//	{
//		fputs(buffer.GetString(), file);
//		fclose(file);
//	}
//	//end
//}

void ExternData::writeSPSkill()
{
	//save as a json
	Document doc;
	doc.SetArray();
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

	std::string fileName;
	switch (dataM->getHType())
	{
	case TypeATK:
		for (int i = 0; i < 5; ++i)
		{
			// SP表示矩阵中一个点的值
			rapidjson::Value SP(rapidjson::kArrayType);
			SP.Clear();
			for (int j = 0; j < 5; ++j)
			{
				SP.PushBack(dataM->ATKSP[i][j], allocator);
			}
			doc.PushBack(SP, allocator);
		}
		fileName = "externData/Skill/ATKSP.json";
		break;

	case TypeDEF:
		for (int i = 0; i < 5; ++i)
		{
			// SP表示矩阵中一个点的值
			rapidjson::Value SP(rapidjson::kArrayType);
			SP.Clear();
			for (int j = 0; j < 5; ++j)
			{
				SP.PushBack(dataM->DEFSP[i][j], allocator);
			}
			doc.PushBack(SP, allocator);
		}
		fileName = "externData/Skill/DEFSP.json";
		break;

	case TypeSPE:
		for (int i = 0; i < 5; ++i)
		{
			// SP表示矩阵中一个点的值
			rapidjson::Value SP(rapidjson::kArrayType);
			SP.Clear();
			for (int j = 0; j < 5; ++j)
			{
				SP.PushBack(dataM->SPESP[i][j], allocator);
			}
			doc.PushBack(SP, allocator);
		}
		fileName = "externData/Skill/SPESP.json";
		break;

	default:
		break;
	}
	
	// save in a file
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	FILE* file = fopen(fileName.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}


void ExternData::writeSkinID()
{
	// save as a json
	Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

	doc.AddMember("ATKSkinId", dataM->ATKSkinId, allocator);
	doc.AddMember("DEFSkinId", dataM->DEFSkinId, allocator);
	doc.AddMember("SPESkinId", dataM->SPESkinId, allocator);

	// save in a file
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);

	FILE* file = fopen("externData/SkinId.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	// end
}