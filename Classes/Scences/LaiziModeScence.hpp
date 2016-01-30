//
//  LaiziModeScence.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#ifndef LaiziModeScence_hpp
#define LaiziModeScence_hpp

#include <stdio.h>
#include "GamePlayRootScence.hpp"

USING_NS_CC;

class LaiziModeScence : public GamePlayRootScence {
public:
    Scene* createScene();
    virtual bool init();
};

#endif /* LaiziModeScence_hpp */
