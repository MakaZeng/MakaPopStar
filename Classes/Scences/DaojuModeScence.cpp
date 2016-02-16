//
//  DaojuModeScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#include "DaojuModeScence.hpp"

Scene* DaojuModeScence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DaojuModeScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool DaojuModeScence::init()
{
    if ( !GamePlayRootScence::init() )
    {
        return false;
    }
    
    Size screenSize = ScreenUtil::getBestScreenSize();

    engine = new DaojuEngine();
    engine->containerView = this->starContainerView;
    engine->initStars();
    
    
    topTool = DaojuModeTopTool::create();
    topTool->setContentSize(Size(screenSize.width,80));
    topTool->setAnchorPoint(Point(0,0));
    topTool->setPosition(Point(0,screenSize.height-80));
    addChild(topTool);
    
    topTool->btn3->addTouchEventListener([this](Ref* r,Widget::TouchEventType t){
        switch (t) {
            case Widget::TouchEventType::BEGAN :
            {
                this->usingDaoju = true;
                break;
            }
            default:
                break;
        }
    });
    
    return true;
}

void DaojuModeScence::clickPoint(Point p)
{
    if (this->usingDaoju) {
        engine->daoJuConfirmHitPoint(p, 4);
        this->usingDaoju = false;
    }else {
        engine->clickPoint(p);
    }
}