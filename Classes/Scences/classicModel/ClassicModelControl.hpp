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
    
    long goal = 0;
    
    CREATE_FUNC(ClassicModelControl);
    
    Size screenSize = ScreenUtil::getBestScreenSize();
    
    bool init(){
        
        if ( !Layer::init() )
        {
            return false;
        }
        
        level=Label::createWithSystemFont("Level 1", "Arial", 40);
        level->setPosition(Point(10,20));
        level->setAnchorPoint(Point(0,0));
        addChild(level);
        
        
        hignScore=Label::createWithSystemFont("Level 1", "Arial", 40);
        hignScore->setPosition(Point(100,20));
        hignScore->setAnchorPoint(Point(0,0));
        addChild(hignScore);
        
        targetScore=Label::createWithSystemFont("Level 1", "Arial", 40);
        targetScore->setPosition(Point(250,20));
        targetScore->setAnchorPoint(Point(0,0));
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
};

#endif /* ClassicModelControl_hpp */
