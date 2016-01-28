//
//  ClassicModelScence.cpp
//  MakaPopStar
//
//  Created by Maka on 28/1/16.
//
//

#include "ClassicModelScence.hpp"

Scene* ClassicModelScence::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassicModelScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClassicModelScence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size contentSize = ScreenUtil::getBestScreenSize();
    
    Layer* starsContainer = Layer::create();
    
    float padding = 40;
    
    starsContainer->setContentSize(Size(contentSize.width - padding , contentSize.height - padding));
    
    starsContainer->setAnchorPoint(Point(0,0));
    
    starsContainer->setPosition(Point(padding/2,padding/2));
    
    addChild(starsContainer);
    
    MatrixManager* core = new MatrixManager();
    
    core->initStars();
    
    LayoutEngine* engine = new LayoutEngine();
    
    engine->layoutStarsWithDataSourceAndLayer(core->dataSource, starsContainer);
    
    return true;
}