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
#include "ClassicModelControl.hpp"

USING_NS_CC;

class LayoutEngine;
class MatrixManager;

class ClassicModelScence : public Layer{
    LayoutEngine* engine;
    MatrixManager* core;
    
public:
    
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    ClassicModelControl* control;
    
    Layer* starsContainer;
    
    Layer* toolBar;
    
    int level = 1;
    
    long target = 1000;
    
    // implement the "static create()" method manually
    CREATE_FUNC(ClassicModelScence);
    
    void nextLevel();
    
    void death(int lockOne,int lockTwo);
};

#endif /* ClassicModelScence_hpp */
