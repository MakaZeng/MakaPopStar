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


class StarModel : public Ref {
public:
    int line;
    int row;
    int type;
};

class StarNode :public Ref {
public:
    StarModel* model;
    Sprite* sprite;
    Point targetCenter;
};

class RootEngine : public Ref {
private:
    CCArray* dataSource;
    CCArray* checkedBlocks;
    CCArray* blocksInSameColor;
    
public:
    int lineCount = 10;
    int rowCount = 10;
    int typeCount = 5;
    
    float perWidth;
    float perHeight;
    CCArray* allNodes;
    
    Layer* containerView;
    
    CCArray* getSameColorStarsWithStar(StarModel * model);
    void destroyStars(CCArray * stars);
    StarModel* getModelForLineAndRow(int line,int row);
    void initStars();
    
private:
    bool checkDeath();
    void layoutStars();
    void checkFourSides(StarModel* model);
    void checkUp(StarModel* model);
    void checkDown(StarModel* model);
    void checkLeft(StarModel* model);
    void checkRight(StarModel* model);
    void relayout(CCArray* dataSource);
    void removeStars(CCArray* stars);
    void removeNodeForModel(StarModel* model);
    StarNode* getNodeForModel(StarModel* model);
    Point getClickStarModelPointWith(Point p);
    Sprite* getRelatedSpriteWith(StarModel* model);
};

#endif /* RootEngine_hpp */
