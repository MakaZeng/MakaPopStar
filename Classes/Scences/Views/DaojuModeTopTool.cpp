//
//  DaojuModeTopTool.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#include "DaojuModeTopTool.hpp"

using namespace cocos2d::ui;

bool DaojuModeTopTool::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    btn1 = Button::create("button.png","button_gray.png","button_gray.png");
    btn1->setAnchorPoint(Point(0,0));
    addChild(btn1);
    
    btn2 = Button::create("button.png","button_gray.png","button_gray.png");
    btn2->setAnchorPoint(Point(0,0));
    addChild(btn2);
    
    btn3 = Button::create("button.png","button_gray.png","button_gray.png");
    btn3->setAnchorPoint(Point(0,0));
    addChild(btn3);
    
    return true;
}