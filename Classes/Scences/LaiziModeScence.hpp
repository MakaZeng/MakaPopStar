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
#include "LaiziEngine.hpp"
#include "GamePlayRootScence.hpp"

USING_NS_CC;

class LaiziModeScence : public GamePlayRootScence {
public:
    CREATE_FUNC(LaiziModeScence);
    static Scene* createScene();
    virtual bool init();
    LaiziEngine* engine;
    virtual void clickPoint(Point p);
};

#endif /* LaiziModeScence_hpp */
