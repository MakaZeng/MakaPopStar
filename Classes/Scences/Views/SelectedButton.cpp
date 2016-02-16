//
//  SelectedButton.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/8.
//
//

#include "SelectedButton.hpp"


bool SelectedButton::init()
{
    if (!Button::init()) {
        return false;
    }
    return true;
}

SelectedButton* SelectedButton::createWithImages(cocos2d::__String *selected, cocos2d::__String *normal)
{
    selected->retain();
    normal->retain();
    SelectedButton* btn = SelectedButton::create();
    btn->selectedString = selected;
    btn->normalString = normal;
    btn->loadTextureNormal(normal->getCString());
    return btn;
}