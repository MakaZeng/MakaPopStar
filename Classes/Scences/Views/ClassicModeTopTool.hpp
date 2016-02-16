//
//  ClassicModeTopTool.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/7.
//
//

#ifndef ClassicModeTopTool_hpp
#define ClassicModeTopTool_hpp

#include <stdio.h>
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"
#include <cocos2d.h>
#include "SelectedButton.hpp"

USING_NS_CC;
using namespace cocos2d::extension;

class ClassicModeTopTool :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ClassicModeTopTool);
    
    Label* levelLabel;
    Label* targetLabel;
    Label* currentLabel;
    
    SelectedButton* pauseButton;
    
};


#endif /* ClassicModeTopTool_hpp */
