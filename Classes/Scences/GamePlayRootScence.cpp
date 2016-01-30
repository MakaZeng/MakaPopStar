//
//  GamePlayRootScence.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#include "GamePlayRootScence.hpp"

bool GamePlayRootScence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size contentSize = ScreenUtil::getBestScreenSize();
    
    starContainerView = Layer::create();
    
    float padding = 10;
    
    starContainerView->setContentSize(Size(contentSize.width - padding , contentSize.height - padding));
    starContainerView->setAnchorPoint(Point(0,0));
    starContainerView->setPosition(Point(padding/2,padding/2));
    addChild(starContainerView);
    
    
    return true;
}