#include "AppDelegate.h"
#include "TollgateScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("Don't Save Me!"); //设置窗口名称
        director->setOpenGLView(glview);
    }

	glview->setFrameSize(480,800); //设置大小(仅Win32)
	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::SHOW_ALL);//屏幕拉伸适配
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);

	auto scene = TollgateScene::scene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
