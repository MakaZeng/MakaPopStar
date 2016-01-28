//
//  MainScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#include "MainScence.hpp"

USING_NS_CC;

Scene* MainScence::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    //    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = MainScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size contentSize = this->getContentSize();
    
    __String* pointer = __String::create("sky.jpg");
    
    Sprite* sp = CommonUtil::runRoundSpriteWithImageName(pointer,40);
    
    sp->setPosition(Point(contentSize.width/2,contentSize.height/2));
    
    addChild(sp);
    
    pointer = __String::create("image_00.png");
    sp = CommonUtil::moveUp(100, Point(contentSize.width/2,contentSize.height - 300), pointer, 1);
    addChild(sp);
    CommonUtil::addRepeatForeverShake(sp);
    
    
    sp = CommonUtil::moveUp(100, Point(contentSize.width/2,contentSize.height - 500), pointer, 1);
    
    CommonUtil::addEaseZoonIn(sp);
    addChild(sp);
    
    this->scheduleUpdate();
    
    return true;
}

void MainScence::update(float dt)
{
    
    static long count = 0;
    count ++;
    
    int rule = 2;
    
    if (count>100) {
        rule = 4;
    }if (count > 100 && count < 1000) {
        rule = 10;
    }else {
        rule = 30;
    }
    
    if (count%rule != 0) {
        return;
    }
    
    Size contentSize = this->getContentSize();
    
    __String* pointer = __String::create("image_00.png");
    
    ParticleSystem* s = CommonUtil::getParticleSystemForImageNameAndLayer(pointer);
    
    s->setPosition(rand()%(int)contentSize.width,rand()%(int)contentSize.height);
    
    addChild(s);
    
    
    pointer = __String::create("Red_button_back.png");
    Button* btn = CommonUtil::buttonForBackImageAndContent(pointer, __String::create("Play"));
    btn->setContentSize(Size(100, 50));
    btn->setPosition(Point(contentSize.width/2,50));
    addChild(btn);
}
