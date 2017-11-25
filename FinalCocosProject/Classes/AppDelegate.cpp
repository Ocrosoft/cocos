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
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("FinalCocosProject", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }
	glview->setFrameSize(960, 640);
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
	director->setAnimationInterval((float)(1.0 / 60));

	auto scene = TollgateScene::scene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
