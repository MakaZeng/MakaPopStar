//
//  LayoutEngine.hpp
//  MakaPopStar
//
//  Created by Maka on 28/1/16.
//
//

#ifndef LayoutEngine_hpp
#define LayoutEngine_hpp

#include <stdio.h>
#include "PopStarCore.hpp"
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"

class StarNode :public Node {
public:
    StarModel* model;
    Sprite* sprite;
    Point targetCenter;
    
public:
    
};

class LayoutEngine : public Ref {
    
public:
    
    float perWidth;
    float perHeight;
    CCArray* allNodes;
    
    Layer* containerLayer;
    
public:
    
    void layoutStarsWithDataSourceAndLayer(CCArray* dataSource , Layer* layer)
    {
        containerLayer = layer;
        
        allNodes = CCArray::create();
        allNodes->retain();
        
        Size contentSize = layer->getContentSize();
        
        perWidth = contentSize.width/20;
        perHeight = perWidth;
        
        CCArray* nameArray = CCArray::create();
        for (int i = 0; i<5; i++) {
            __String* s = __String::createWithFormat("image_0%d.png",i);
            nameArray->addObject(s);
        }
        
        Size screenSize = ScreenUtil::getBestScreenSize();
        
        for (int i = 0; i<dataSource->count(); i++) {
            for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
                StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
                model->line = i;
                model->row = j;
                
                __String* file = (__String*)nameArray->objectAtIndex(model->type);
                Sprite* bSprite = Sprite::create(file->getCString());
                bSprite->setPosition(Point((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth + screenSize.height));
                ActionInterval * moveBy = MoveBy::create(1+i*.05+j*.05,Vec2(0, 0 - screenSize.height));
                bSprite->runAction(moveBy);
                bSprite->setScale(CommonUtil::getScaleForTargetWithImage(perWidth, bSprite));
                layer->addChild(bSprite);
                
                StarNode* node = new StarNode();
                node->sprite = bSprite;
                node->model = model;
                node->targetCenter = bSprite->getPosition();
                allNodes->addObject(node);
            }
        }
    }
    
    
    Point getClickStarModelPointWith(Point p)
    {
        int row = p.y / this->perHeight;
        int line = p.x / this->perWidth;
        
        return Vec2(line, row);
    }
    
    Sprite* getRelatedSpriteWith(StarModel* model)
    {
        for(int i = 0 ; i < allNodes->count() ; i ++)
        {
            StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
            if (n->model == model) {
                return n->sprite;
            }
        }
        return NULL;
    }
    
    StarNode* getNodeForModel(StarModel* model)
    {
        for(int i = 0 ; i < allNodes->count() ; i ++)
        {
            StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
            if (n->model == model) {
                return n;
            }
        }
        return NULL;
    }
    
    void removeNodeForModel(StarModel* model)
    {
        for(int i = 0 ; i < allNodes->count() ; i ++)
        {
            StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
            if (n->model == model) {
                allNodes->removeObject(n);
                return;
            }
        }
    }
    
    void removeStars(CCArray* stars)
    {
        for(int i = 0 ; i < stars->count() ; i ++)
        {
            StarModel* model = (StarModel*)stars->objectAtIndex(i);
            Sprite* sp = getRelatedSpriteWith(model);
            removeNodeForModel(model);
        }
    }
    
    void relayout(CCArray* dataSource)
    {
        CCArray* emptyArray = CCArray::create();
        
        for (int i = 0; i<dataSource->count(); i++) {
            CCArray* arr = (CCArray*)dataSource->objectAtIndex(i);
            
            if (arr->count() == 0) {
                emptyArray->addObject(arr);
            }
        }
        
        dataSource->removeObjectsInArray(emptyArray);
        
        for (int i = 0; i<dataSource->count(); i++) {
            for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
                StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
                
                model->line = i;
                model->row = j;
                
                StarNode* node = getNodeForModel(model);
                
                Point p = node->sprite->getPosition();
                Point t = ccp((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth);
                
                if (p.x != t.x || p.y != t.y) {
                    CCActionInterval * moveBy = CCMoveBy::create(0.3,Vec2(t.x-p.x, t.y-p.y));
                    CCActionInterval * actionmoveback= moveBy;
                    node->sprite->runAction(actionmoveback);
                    allNodes->addObject(node);
                }
                
            }
        }
    }
    
};

#endif /* LayoutEngine_hpp */
