//
//  ClassicModelScence.hpp
//  MakaPopStar
//
//  Created by Maka on 28/1/16.
//
//

#ifndef ClassicModelScence_hpp
#define ClassicModelScence_hpp

#include <stdio.h>
#include <cocos2d.h>
#include "LayoutEngine.hpp"
#include "PopStarCore.hpp"

USING_NS_CC;

class ClassicModelScence : public Layer{
    
public:
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ClassicModelScence);
};

#endif /* ClassicModelScence_hpp */
