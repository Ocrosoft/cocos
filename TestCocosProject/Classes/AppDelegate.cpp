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
    /*初始化Director*/
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		/*修改标题和大小*/
		glview = GLViewImpl::createWithRect("runrunrun", Rect(0, 0, 1024, 640)); 
        director->setOpenGLView(glview);
    }
	/*修改分辨率和缩放*/
	glview->setDesignResolutionSize(1024, 640, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
    director->setAnimationInterval((float)(1.0 / 60));
	/*创建场景*/
    auto scene = TollgateScene::scene();
    director->runWithScene(scene);
	/*返回真*/
    return true;
}
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	/*暂停背景音乐*/
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	/*继续播放背景音乐*/
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
