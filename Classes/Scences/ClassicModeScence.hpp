//
//  ClassicModeScence.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#ifndef ClassicModeScence_hpp
#define ClassicModeScence_hpp

#include <stdio.h>
#include "ClassicEngine.hpp"
#include "GamePlayRootScence.hpp"
#include <cocos2d.h>

using namespace cocos2d::extension;

class ClassicModeScence : public GamePlayRootScence{
public:
    CREATE_FUNC(ClassicModeScence);
    static Scene* createScene();
    virtual bool init();
    ClassicEngine* engine;
    virtual void clickPoint(Point p);
};

#endif /* ClassicModeScence_hpp */
