//
//  LaiziModeScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#include "LaiziModeScence.hpp"

Scene* LaiziModeScence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LaiziModeScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool LaiziModeScence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}