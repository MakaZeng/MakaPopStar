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
    
    CommonUtil::getTailImageSpriteWithImageName(__String::create("img_gray_background.png"), this , false);
    
    Size contentSize = ScreenUtil::getBestScreenSize();
    
    starContainerView = Layer::create();
    
    float padding = 400;
    
    starContainerView->setContentSize(Size(contentSize.width - padding , contentSize.height - padding));
    starContainerView->setAnchorPoint(Point(0,0));
    starContainerView->setPosition(Point(padding/2,padding/4));
    addChild(starContainerView);
    
    
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_2(GamePlayRootScence::onTouchesBegan,this);
    listen->onTouchesMoved = CC_CALLBACK_2(GamePlayRootScence::onTouchesMoved,this);
    listen->onTouchesEnded = CC_CALLBACK_2(GamePlayRootScence::onTouchesEnded,this);
    listen->onTouchesCancelled = CC_CALLBACK_2(GamePlayRootScence::onTouchesCancelled,this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
    
    
    return true;
}

//触摸事件开始，手指按下时
void GamePlayRootScence::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
    for(auto &item : touches)
    {
        auto touch = item;
        auto pos1 = touch->getLocation();
        auto pos2 = touch->getLocationInView();
        auto pos3 = Director::getInstance()->convertToUI(pos2);
        this->clickPoint(Point(pos1));
    }
}

void GamePlayRootScence::clickPoint(Point p)
{
    
}

//触摸移动事件，也就是手指在屏幕滑动的过程
void GamePlayRootScence::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}
//触摸事件结束，也就是手指松开时
void GamePlayRootScence::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断
void GamePlayRootScence::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{

}
