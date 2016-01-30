//
//  MainScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"
#include "MainScence.hpp"
//#include "LaiziModeScence.hpp"

USING_NS_CC;

Scene* MainScence::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    
    this->scheduleUpdate();
    
    return true;
}

void MainScence::update(float dt)
{
    Size contentSize = this->getContentSize();
    __String* pointer = __String::create("star.png");
    ParticleSystem* s = CommonUtil::getParticleSystemForImageNameAndLayer(pointer);
    s->setPosition(rand()%(int)contentSize.width,rand()%(int)contentSize.height);
    addChild(s);
}
