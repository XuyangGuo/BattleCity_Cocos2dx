/***********************************************

该类是游戏开始运行之前的预加载页面，
主要功能包括图片、plist、json、音效的预加载，计时器的开启

***********************************************/

#include "LoadingScene.h"
#include "input\keyboardInput.h"
#include "SceneM.h"
#include "data\DataM.h"
#include "data\SuccessData.h"
#include "data\StayTime.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class StayTime;
bool LoadingScene::init()
{
	/* 其实没多少资源，并不需要预加载，用到的时候再加载就成 */ 
	//乱讲，资源有很多好不好 -_-!!
	const char* image[] =
	{
		"Gear.png" ,"Border.png ","Brick.png", "Grass.png", "Grid1.png","Grid2.png","Grid3.png","Grid4.png","Brick1.png","Brick0.png",
		"Rectangle.png","HP1.png","HP0.png","MP0.png","MP1.png", "Progress1.png","Progress0.png","Ruler.png","Cursor.png",
		"Home0.png","Home1.png","WaterBorder.png","HomePage0.jpg","HomePage1.jpg" ,"HomePage2.jpg",
		"Level1.png","Level2.png","Level3.png","Level4.png","Level5.png","Level6.png","Level7.png","Level8.png","Level9.png","Level10.png" ,"Level11.png","Level12.png","Level13.png","Level14.png","Level15.png",
		"LevelBackground.jpg","Normal.png","SelectedRect.png","Shadow.png","Star1.png","Star2.png","Star3.png",
		"Hero0.png","Hero1.png","Hero2.png","BGHero.png","ThreeTanks.png","BigCircle.png","FullBigCircle.png",
		"Fail0.png","Fail1.png","Pause0.png","Pause1.png","Star1_0.png","Star1_1.png","Star2_0.png","Star2_1.png","Star3_0.png","Star3_1.png",
		"DownArrow.png","RightArrow.png","SkillRect.png","Bullet0.png","Bullet1.png","Bullet2.png",
		"Skin0_0.png","Skin0_1.png","Skin1_1.png","Skin2_1.png","Skin1_0.png","Skin2_0.png","Skin2_2.png","Skin1_2.png","Skin0_2.png","skinArrow.png",
		"playertank0_0.png","playertank1_0.png","playertank2_0.png","playertank0_1.png","playertank1_1.png","playertank2_1.png","playertank0_2.png","playertank1_2.png","playertank2_2.png","bonus_1.png","bonus_2.png","bonus_3.png","bonus_4.png",
		"EnemyTank1.png","EnemyTank2.png","EnemyTank3.png","EnemyTank4.png","EnemyTank5.png","EnemyTankHPEmpty.png","EnemyTankHPFull.png","Cross.png","Sheild.png",
		"Born0.png","Born1.png","whitebg.png","goldcup.png","greybg.png","greycup.png","backmenu1.png","backmenu2.png","difficulty0&0.png","difficulty1&1.png","difficulty2&2.png","difficulty3&3.png","difficulty4&4.png",
		"difficulty0.png","difficulty1.png","difficulty2.png","difficulty3.png","difficulty4.png","editElement.png","editorBottom.png","editorButton.png","eraser.png","mapItem.png","namemenu.png","shadowSelector.png","inputPosition.png","lock.png",
		"Skin1_2_1.png","Skin2_2_1.png","Skin0_2_1.png","Skin1_1_1.png","Skin0_1_1.png","Skin2_1_1.png","success1_0.png","success1_1.png","success2_0.png","success2_1.png","success3_0.png","success3_1.png","success4_0.png","success4_1.png","success5_0.png",
		"success5_1.png","success6_0.png","success6_1.png","success7_0.png","success7_1.png","success8_0.png","success8_1.png","success9_0.png","success9_1.png","success10_0.png","success10_1.png"
	};
	for (auto name : image)
	{
		Director::getInstance()->getTextureCache()->addImage(name);
	}
	const char* plist[] = { "Water.plist", "bomb.plist", 
		"BigSkill.plist"
	};
	for (auto name : plist)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(name);
	}

	//主要是json初始化
	DataM::getInstance();
	SuccessData::getInstance();
	
	//键盘初始化
	auto keyboardInput = KeyboardInput::create();
	Director::getInstance()->setNotificationNode(keyboardInput);

	/* 初始化的时候无法切换场景，故延迟一帧再切换场景 */
	this->scheduleOnce([&](float dt) {
		SceneM::getInstance()->changeScene(kMenuScene);
	}, 0.0f, "delay");	

	//getTime,用来设置随机函数
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;
	int srandNum = hour * 3600 + minute * 60 + second;
	srand(++srandNum);

	//开启时间计时，用来记录成就
	StayTime::start();

	//声音预加载
	const char* preMusic[] = {
		"atk0.mp3","atk1.mp3","atk2.mp3","atk3.mp3","atk4.mp3","atk5.mp3","atk6.mp3","atkBigSkill.mp3" ,"editScene0.mp3","editScene1.mp3","editScene2.mp3","gameScene0.mp3" ,
		"gameScene1.mp3","gameScene2.mp3","gameScene3.mp3","gameScene4.mp3","gameScene5.mp3","heroScene.mp3","loseGame.mp3","menu_levelScene.mp3","successScene.mp3",
		"victory.mp3",
		"speAttack.mp3","skillScene8.mp3","skillScene7.mp3","skillScene6.mp3","skillScene5.mp3","skillScene4.mp3","skillScene3.mp3","skillScene2.mp3","skillScene1.mp3","skillScene0.mp3","pause.mp3","noCanDoInSkillScene.mp3","gridBroken.mp3",
		"defShield1.mp3","defShield0.mp3","defRebirth.mp3","defAttack.mp3","def6.mp3","def5.mp3","def4.mp3","def3.mp3","def2.mp3","def1.mp3","def0.mp3","buttonMouseMoveOverInSikllScene.mp3","brickBroken3.mp3","brickBroken2.mp3","brickBroken1.mp3","brickBroken0.mp3",
		"atkAttack.mp3","atkAttackWithAOE.mp3","bigSkillReady.mp3","hit0.mp3","hit1.mp3","homeBroken.mp3","homeBroken_1.mp3","removeTank0.mp3","removeTank1.mp3","removeTank2.mp3","removeTank3.mp3","removeTank4.mp3","removeTank5.mp3","removeTank6.mp3","speBigSkill.mp3"
	};
	for (auto name : preMusic)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name);
	}

	return true;
}