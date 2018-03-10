#include "AppDelegate.h"
#include "data\Global.h"
#include "scene\SceneM.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("Tank", Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
        director->setOpenGLView(glview);
    }

	director->getOpenGLView()->setDesignResolutionSize(SCREEN_WIDTH, SCREEN_HEIGHT, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto fileUtils = FileUtils::getInstance();
	fileUtils->addSearchPath("fonts");
	fileUtils->addSearchPath("images");
	fileUtils->addSearchPath("configs");
	fileUtils->addSearchPath("sounds");
	fileUtils->addSearchPath("externData");
	fileUtils->addSearchPath("externData/skill");
	fileUtils->addSearchPath("externData/successData");
	fileUtils->addSearchPath("images/tank");
	fileUtils->addSearchPath("images/levelScene");
	fileUtils->addSearchPath("images/skill");
	fileUtils->addSearchPath("images/state");
	fileUtils->addSearchPath("images/mapEditor");
	fileUtils->addSearchPath("images/success");
	fileUtils->addSearchPath("costumMap");
	fileUtils->addSearchPath("music/background70");
	fileUtils->addSearchPath("music/background70");
	fileUtils->addSearchPath("music/music90");
	fileUtils->addSearchPath("music/sound80");
	fileUtils->addSearchPath("music/talk100");

	SceneM::getInstance()->changeScene(kLoadingScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{

}
