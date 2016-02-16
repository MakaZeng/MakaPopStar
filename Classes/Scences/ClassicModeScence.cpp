//
//  ClassicModeScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#include "ClassicModeScence.hpp"
#include "ClassicModeTopTool.hpp"

Scene* ClassicModeScence::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassicModeScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ClassicModeScence::init()
{
    if ( !GamePlayRootScence::init() )
    {
        return false;
    }
    
    Size contentSize = ScreenUtil::getBestScreenSize();
    
    engine = new ClassicEngine();
    engine->containerView = this->starContainerView;
    engine->initStars();
    
    ClassicModeTopTool* tool = ClassicModeTopTool::create();
    tool->setContentSize(Size(contentSize.width , TOP_TOOLBAR_HEIGHT));
    tool->setAnchorPoint(Point(0,0));
    tool->setPosition(Point(0,contentSize.height-TOP_TOOLBAR_HEIGHT));
    addChild(tool);
    
    return true;
}



void ClassicModeScence::clickPoint(Point p)
{
    engine->clickPoint(p);
}
