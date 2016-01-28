//
//  MainScence.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#ifndef MainScence_hpp
#define MainScence_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"

class MainScence : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScence);
    
    void switchToClassicMode();
    void update(float dt);
};


#endif /* MainScence_hpp */
