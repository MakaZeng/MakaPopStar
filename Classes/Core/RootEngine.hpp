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
private:
    CCArray* dataSource;
    CCArray* checkedBlocks;
    CCArray* blocksInSameColor;
    CCArray* allNodes;
public:
    
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
    
private:
    bool checkDeath();
    void checkFourSides(StarModel* model);
    void checkUp(StarModel* model);
    void checkDown(StarModel* model);
    void checkLeft(StarModel* model);
    void checkRight(StarModel* model);
};

#endif /* RootEngine_hpp */
