//
//  GamePlayRootScence.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#ifndef GamePlayRootScence_hpp
#define GamePlayRootScence_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ScreenUtil.hpp"
#include "CommonUtil.hpp"

USING_NS_CC;

class GamePlayRootScence : public Layer {
public:
    virtual bool init();
    CREATE_FUNC(GamePlayRootScence);
    Layer* rootContaienrView;
    Layer* backgroundView;
    Layer* starContainerView;
    
};

#endif /* GamePlayRootScence_hpp */
