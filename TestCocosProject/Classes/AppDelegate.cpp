#include "AppDelegate.h"
#include "TollgateScene.h"
USING_NS_CC;
AppDelegate::AppDelegate() {}
AppDelegate::~AppDelegate() {}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}
bool AppDelegate::applicationDidFinishLaunching() {
    /*��ʼ��Director*/
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		/*�޸ı���ʹ�С*/
		glview = GLViewImpl::createWithRect("runrunrun", Rect(0, 0, 1024, 640)); 
        director->setOpenGLView(glview);
    }
	/*�޸ķֱ��ʺ�����*/
	glview->setDesignResolutionSize(1024, 640, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
    director->setAnimationInterval((float)(1.0 / 60));
	/*��������*/
    auto scene = TollgateScene::scene();
    director->runWithScene(scene);
	/*������*/
    return true;
}
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	/*��ͣ��������*/
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	/*�������ű�������*/
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
