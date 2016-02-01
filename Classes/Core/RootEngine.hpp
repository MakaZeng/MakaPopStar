//
//  RootEngine.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#ifndef RootEngine_hpp
#define RootEngine_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class StarModel;

class StarNode :public Ref {
public:
    StarModel* model;
    Sprite* sprite;
    Point targetCenter;
};

class StarModel : public Ref {
public:
    StarNode* node;
    int line;
    int row;
    int type;
};

class RootEngine : public Ref {

public:
    
    CCArray* dataSource;
    CCArray* checkedBlocks;
    CCArray* blocksInSameColor;
    CCArray* allNodes;

    
    int lineCount = 10;
    int rowCount = 10;
    int typeCount = 5;
    
    float perWidth;
    float perHeight;
    
    Layer* containerView;
    
    void initStars();
    void clickPoint(Point p);
    CCArray* getSameColorStarsWithStar(StarModel * model);
    void highLightedSeltectedArray(CCArray* array);
    void destroySlectedArray(CCArray* array);
    StarModel* getModelForLineAndRow(int line,int row);
    
    bool checkDeath();
    void checkFourSides(StarModel* model);
    virtual void checkUp(StarModel* model);
    virtual void checkDown(StarModel* model);
    virtual void checkLeft(StarModel* model);
    virtual void checkRight(StarModel* model);
};

#endif /* RootEngine_hpp */
