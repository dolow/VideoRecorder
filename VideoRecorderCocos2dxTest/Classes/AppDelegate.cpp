#include "AppDelegate.h"
#include "HelloWorldScene.h"

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

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    glview->getEAGLView();
    
    
    director->setContentScaleFactor(2.0f);
    
    Size screenSize = director->getOpenGLView()->getFrameSize();
    
    float shorter = 320.0f;
    float longer  = 568.0f;
    
    ResolutionPolicy policy = ResolutionPolicy::SHOW_ALL;
    
    if (screenSize.width > screenSize.height) {
        if (screenSize.width == 1136.0)
            policy = ResolutionPolicy::EXACT_FIT;
        else if (screenSize.width < 1136.0f || screenSize.height < 640.0f)
            longer = 480.0f;
    }
    
    director->getOpenGLView()->setDesignResolutionSize(longer, shorter, policy);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
