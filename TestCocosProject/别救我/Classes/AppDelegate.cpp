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
		glview = GLViewImpl::create("Don't Save Me!"); //���ô�������
        director->setOpenGLView(glview);
    }

	glview->setFrameSize(480,800); //���ô�С(��Win32)
	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::SHOW_ALL);//��Ļ��������
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
