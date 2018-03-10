#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum SceneType			// 场景类型 
{
	kLoadingScene,		// 加载场景 
	kMenuScene,			// 菜单场景 
	kLevelScene,		// 关卡过渡场景、选关 
	kGameScene,			// 游戏场景 
	kGameOverScene,		// 游戏结束场景
	kSelectHeroScene,	// 选择英雄界面
	kHeroScene,			// 英雄页面
	kSuccessScene,		// 成就页面
	kSkillScene,		// 技能和皮肤页面
	kCustomScene,		// 自定义页面
	kEditorScene,		// 自定义页面2
};

enum TransitionType
{
	kTransitionNone,
	kTransitionSplitRows,
	kTransitionFade,
	kTransitionCrossFade,
	kTransitionPageTurn_false,
	kTransitionPageTurn_true,
	kTransitionZoomFlipAngular_RIGHT_OVER,
	kTransitionZoomFlipAngular_LEFT_OVER,
	kTransitionProgressRadialCCW
};

class SceneM :public Ref
{
public:
	static SceneM *getInstance();
	virtual bool init();
	/* 切换场景 */
	void changeScene(SceneType sceneType,TransitionType kTransitionType = kTransitionNone);
	/* 获取当前场景的图层 */
	Layer *getCurScene();

private:
	Layer *_layer;
};
