#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(HelloWorld);
    
private:
    DrawNode* _drawNode = nullptr;
    
    float _spb = 0.47f;
    float _y   = 0.0f;
};

#endif // __HELLOWORLD_SCENE_H__
