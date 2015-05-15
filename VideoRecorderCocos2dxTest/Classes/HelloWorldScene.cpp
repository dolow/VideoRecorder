#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "VideoRecorderBridge.h"

using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Label* l = Label::createWithSystemFont("testing", "Arial", 32);
    l->setPosition(Vec2(visibleSize / 2) - Vec2(160.0f, 80.0f));
    this->addChild(l, 1);
    
    l->runAction(RepeatForever::create(Sequence::createWithTwoActions(
        Spawn::createWithTwoActions(
            Sequence::createWithTwoActions(
                EaseOut::create(TintTo::create(_spb / 2, 224.0f, 224.0f, 224.0f), 1.5f),
                EaseIn::create(TintTo::create(_spb / 2, 128.0f, 128.0f, 128.0f), 1.5f)),
            JumpTo::create(_spb, Vec2(visibleSize / 2) + Vec2(160.0f, -80.0f), 160.0f, 1)),
        Spawn::createWithTwoActions(
            Sequence::createWithTwoActions(
                EaseOut::create(TintTo::create(_spb / 2, 224.0f, 224.0f, 224.0f), 1.5f),
                EaseIn::create(TintTo::create(_spb / 2, 128.0f, 128.0f, 128.0f), 1.5f)),
            JumpTo::create(_spb, Vec2(visibleSize / 2) - Vec2(160.0f, 80.0f), 160.0f, 1))
    )));
    
    
    _drawNode = DrawNode::create();
    this->addChild(_drawNode);
    
    MenuItemLabel* button = MenuItemLabel::create(Label::createWithSystemFont("RECORD", "Arial", 16), [](Ref* self){
        Label* label = static_cast<Label*>(static_cast<MenuItemLabel*>(self)->getLabel());
        if (label->getString() == "RECORD") {
            static_cast<Label*>(static_cast<MenuItemLabel*>(self)->getLabel())->setString("STOP");
            VideoRecorderBridge::begin();
        }
        else {
            static_cast<Label*>(static_cast<MenuItemLabel*>(self)->getLabel())->setString("RECORD");
            VideoRecorderBridge::end();
        }
    });
    
    button->setAnchorPoint(Vec2(1.0f, 0.0f));
    button->setPosition(Vec2(visibleSize.width, 0.0f));
    
    Menu* menu = Menu::create(button, nullptr);
    menu->ignoreAnchorPointForPosition(false);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setContentSize(visibleSize);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu, 10);
    
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{
    _drawNode->clear();
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int lines = 6;
    
    _y += dt / _spb * (visibleSize.height / lines);
    if (_y > visibleSize.height)
        _y -= visibleSize.height;
    
    for (int i = 0; i < lines; i++) {
        float y1 = _y - visibleSize.height  / lines * i;
        
        if (y1 > visibleSize.height)
            y1 -= visibleSize.height;
        if (y1 < 0.0f)
            y1 += visibleSize.height;
        
        float y2 = y1 - (visibleSize.height - y1) / 6;
        
        Vec2 verts[4] = {
            Vec2(0.0f, y1), Vec2(visibleSize.width, y1),
            Vec2(visibleSize.width, y2), Vec2(0.0f, y2)
        };
        
        float b = 0.8f * (y1 / visibleSize.height);
        
        _drawNode->drawPolygon(verts, 4, Color4F(b, b, b, 1.0f), 0.0f, Color4F(b, b, b, 1.0f));
    }
}
