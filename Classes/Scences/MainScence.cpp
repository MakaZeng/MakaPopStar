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
    
    __String* pointer = __String::create("sky.jpg");
    
    Sprite* sp = CommonUtil::runRoundSpriteWithImageName(pointer);
    
    sp->setPosition(Point(this->getContentSize().width/2,this->getContentSize().height/2));
    
    addChild(sp);
    
    return true;
}