//
//  DaojuModeTopTool.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#ifndef DaojuModeTopTool_hpp
#define DaojuModeTopTool_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"

USING_NS_CC;

class DaojuModeTopTool:public Layer {
public:
    Button* btn1;
    Button* btn2;
    Button* btn3;
    virtual bool init();
    CREATE_FUNC(DaojuModeTopTool);
};

#endif /* DaojuModeTopTool_hpp */
