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
    
    
    CommonUtil::getTailImageSpriteWithImageName(__String::create("img_background"), this ,true);
    
    
    Sprite* sp = Sprite::create("img_home.png");
    sp->setAnchorPoint(Point(0,0));
    addChild(sp);
    
    this->scheduleUpdate();
    
    return true;
}

void MainScence::update(float dt)
{

}
