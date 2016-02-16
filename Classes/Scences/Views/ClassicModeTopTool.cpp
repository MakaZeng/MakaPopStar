//
//  ClassicModeTopTool.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/7.
//
//

#include "ClassicModeTopTool.hpp"

bool ClassicModeTopTool::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size screenSize = ScreenUtil::getBestScreenSize();

    levelLabel = Label::createWithSystemFont("Level:01", FONT_NAME, FONT_SIZE);
    levelLabel->setAnchorPoint(Point(0,1));
    levelLabel->setPosition(Point(20 , TOP_TOOLBAR_HEIGHT - 20));
    addChild(levelLabel);
    
    targetLabel = Label::createWithSystemFont("Target:", FONT_NAME, FONT_SIZE+5);
    targetLabel->setAnchorPoint(Point(0.5,1));
    targetLabel->setTextColor(Color4B::ORANGE);
    targetLabel->setPosition(Point(screenSize.width/2 , TOP_TOOLBAR_HEIGHT-20));
    addChild(targetLabel);
    
    currentLabel = Label::createWithSystemFont("Current:\n10086", FONT_NAME, FONT_SIZE);
    currentLabel->setAnchorPoint(Point(1,1));
    currentLabel->setPosition(Point( screenSize.width - 20 , TOP_TOOLBAR_HEIGHT - 20));
    currentLabel->setAlignment(cocos2d::TextHAlignment::RIGHT);
    addChild(currentLabel);
    
    
    pauseButton = SelectedButton::createWithImages(__String::create("play.png"), __String::create("pause.png"));
    pauseButton->setContentSize(Size(64,64));
    pauseButton->setAnchorPoint(Point(0,1));
    pauseButton->setPosition(Point(30,10));
    pauseButton->addTouchEventListener([this](Ref* r,Widget::TouchEventType type){
        if (type == Widget::TouchEventType::BEGAN) {
            pauseButton->Selected = !pauseButton->Selected;
            if (pauseButton->Selected) {
                pauseButton->loadTextureNormal(pauseButton->selectedString->getCString());
            }else {
                pauseButton->loadTextureNormal(pauseButton->normalString->getCString());
            }
        }
    });
    addChild(pauseButton);
    
    return true;
}