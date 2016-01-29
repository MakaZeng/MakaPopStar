//
//  ClassicModelControl.hpp
//  MakaPopStar
//
//  Created by Maka on 29/1/16.
//
//

#ifndef ClassicModelControl_hpp
#define ClassicModelControl_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"

USING_NS_CC;

class ClassicModelControl : public Layer {
    
public:
    
    Label* level;
    Label* hignScore;
    Label* targetScore;
    Label* currentScore;
    Label* HighScoreLabel;
    
    long goal = 0;
    long le = 1;
    long t = 1000;
    long high = 0;
    
    CREATE_FUNC(ClassicModelControl);
    
    Size screenSize = ScreenUtil::getBestScreenSize();
    
    bool init(){
        
        if ( !Layer::init() )
        {
            return false;
        }
        
        level=Label::createWithSystemFont("关卡:1", "Arial", 30);
        level->setPosition(Point(10,20));
        level->setAnchorPoint(Point(0,1));
        addChild(level);
        
        
        hignScore=Label::createWithSystemFont("历史最高分", "Arial", 30);
        hignScore->setPosition(Point(screenSize.width-20,80));
        hignScore->setAnchorPoint(Point(1,1));
        addChild(hignScore);
        
        HighScoreLabel=Label::createWithSystemFont("", "Arial", 25);
        HighScoreLabel->setPosition(Point(screenSize.width-20,50));
        HighScoreLabel->setAnchorPoint(Point(1,1));
        addChild(HighScoreLabel);
        
        targetScore=Label::createWithSystemFont("目标分数:", "Arial", 30);
        targetScore->setPosition(Point(10,80));
        targetScore->setAnchorPoint(Point(0,1));
        addChild(targetScore);
        
        currentScore=Label::createWithSystemFont("0", "Arial", 60);
        currentScore->setPosition(Point(screenSize.width/2,0));
        currentScore->setTextColor(Color4B::ORANGE);
        addChild(currentScore);
        
        return true;
    }
    
    void appendScore(long score)
    {
        goal+=score;
        currentScore->setString(__String::createWithFormat("%ld",goal)->getCString());
    }
    
    void setLe(int le){
        le = le;
        level->setString(__String::createWithFormat("关卡:%d",le)->getCString());
    }
    
    void setTarget(long tar)
    {
        t = tar;
        targetScore->setString(__String::createWithFormat("目标分数:%ld",t)->getCString());
    }
    
    void setHigh(long hig)
    {
        high = hig;
        HighScoreLabel->setString(__String::createWithFormat("%ld",high)->getCString());
    }
};

#endif /* ClassicModelControl_hpp */
