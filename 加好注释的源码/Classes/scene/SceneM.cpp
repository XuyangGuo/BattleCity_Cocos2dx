/***********************************************

该类是游戏所有场景的管理类，
游戏场景的跳转通过该类下面的changeScene函数实现，
主要功能包括页面跳转、转换动画的制作

***********************************************/

#include "SceneM.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "LevelScene.h"
#include "HeroScene.h"
#include "SelectHeroScene.h"
#include "GameScene.h"
#include "SkillScene.h"
#include "SuccessScene.h"
#include "EditorScene.h"
#include "2d\CCTransition.h"
#include "EditScene.h"

static SceneM *s_SceneM = nullptr;

SceneM *SceneM::getInstance()
{
	if (nullptr == s_SceneM)
	{
		s_SceneM = new (std::nothrow)SceneM();
		CCASSERT(s_SceneM, "FATAL!Not enough Memory.");
		s_SceneM->init();
	}
	return s_SceneM;
}

bool SceneM::init()
{
	return true;
}
//转换场景，方便以后调用
void SceneM::changeScene(SceneType sceneType, TransitionType transitionType)
{
	Scene *scene = Scene::create();
	switch (sceneType)
	{
	case kLoadingScene:
		_layer = LoadingScene::create();
		break;
	case kMenuScene:
		_layer = MenuScene::create();
		break;
	case kLevelScene:
		_layer = LevelScene::create();  
		break;
	case kSelectHeroScene:
		_layer = SelectHeroScene::create();
		break;
	case kHeroScene:
		_layer = HeroScene::create();
		break;
	case kSuccessScene:
		_layer = SuccessScene::create();
		break;
	case kGameScene:
		_layer = GameScene::create();
		break;
	case kSkillScene:
		_layer = SkillScene::create();
		break;
	case kCustomScene:
		_layer = EditScene::create();
		break;
	case kEditorScene:
		_layer = EditorScene::create();
		break;
	default:
		break;
	}
	scene->addChild(_layer);
	auto curScene = Director::getInstance()->getRunningScene();

	switch (transitionType)
	{
	case kTransitionSplitRows:
		scene = TransitionSplitRows::create(0.9f,scene);
		break;
	case kTransitionFade:
		scene =	TransitionFade::create(0.6f, scene);
		break;
	case kTransitionCrossFade:
		scene = TransitionCrossFade::create(0.6f, scene);
		break;
	case kTransitionPageTurn_false:
		scene = TransitionPageTurn::create(0.6f, scene, false);
		break;
	case kTransitionPageTurn_true:
		scene = TransitionPageTurn::create(0.6f, scene, true);
		break;
	case kTransitionZoomFlipAngular_RIGHT_OVER:
		scene = TransitionZoomFlipAngular::create(0.6f, scene, TransitionScene::Orientation::RIGHT_OVER);
		break;
	case kTransitionZoomFlipAngular_LEFT_OVER:
		scene = TransitionZoomFlipAngular::create(0.6f, scene, TransitionScene::Orientation::LEFT_OVER);
		break;
	case kTransitionProgressRadialCCW:
		scene = TransitionProgressRadialCCW::create(0.6f, scene);
		break;
	default:
		break;
	}
	{
		if (curScene)
		{
			Director::getInstance()->replaceScene(scene);
		}
		else
		{
			Director::getInstance()->runWithScene(scene);
		}
	}
}

