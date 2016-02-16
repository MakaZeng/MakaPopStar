//
//  SelectedButton.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/8.
//
//

#ifndef SelectedButton_hpp
#define SelectedButton_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "ScreenUtil.hpp"
#include "CommonUtil.hpp"

USING_NS_CC;

class SelectedButton:public Button {
public:
    bool Selected;
    __String* selectedString;
    __String* normalString;
    virtual bool init();
    CREATE_FUNC(SelectedButton);
    static SelectedButton* createWithImages(__String* selected , __String* normal);
};

#endif /* SelectedButton_hpp */
