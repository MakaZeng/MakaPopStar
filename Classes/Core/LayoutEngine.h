//
//  LayoutEngine.h
//  MakaPopStar
//
//  Created by Maka on 26/1/16.
//
//

#ifndef LayoutEngine_h
#define LayoutEngine_h

#include "cocos2d.h"
#include "PopStarCore.h"

using namespace cocos2d;

class StarNode :public Node {
public:
    
    StarModel* model;
    
    Sprite* sprite;
    
public:
    
};

class LayoutEngine : public Ref {

public:
    
    float perWidth;
    float perHeight;
    CCArray* allNodes;
    
public:
    
    void layoutStarsWithDataSourceAndLayer(CCArray* dataSource , Layer* layer)
    {
        
        CCArray* emptyArray = CCArray::create();
        
        for (int i = 0; i<dataSource->count(); i++) {
            CCArray* arr = (CCArray*)dataSource->objectAtIndex(i);
            
            if (arr->count() == 0) {
                emptyArray->addObject(arr);
            }
        }
        
        dataSource->removeObjectsInArray(emptyArray);
        
        
        layer->removeAllChildren();
        
        allNodes = CCArray::create();
        allNodes->retain();
        
        Rect rect = layer->getBoundingBox();
        
        perWidth = rect.size.width/10;
        perHeight = perWidth;
        
        CCArray* nameArray = CCArray::create();
        
        String* blue = String::create("blue.png");
        String* green = String::create("green.png");
        String* orange = String::create("orange.png");
        String* purple = String::create("purple.png");
        String* red = String::create("red.png");
        
        nameArray->addObject(blue);
        nameArray->addObject(green);
        nameArray->addObject(orange);
        nameArray->addObject(purple);
        nameArray->addObject(red);
        
        for (int i = 0; i<dataSource->count(); i++) {
            for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
                StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
                CCImage* image = new CCImage();
                String* fileName = (String*)nameArray->objectAtIndex(model->type);
                String path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName->getCString());
                image->initWithImageFile(path.getCString());
                
                CCTexture2D* texture = new CCTexture2D;
                texture->initWithImage(image);
                CCSprite* bSprite = CCSprite::createWithTexture(texture);
                
                bSprite->setPosition(ccp((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth));
                
                model->line = i;
                model->row = j;
                
                bSprite->setScale(2, 2);
                
                layer->addChild(bSprite);
                
                StarNode* node = new StarNode();
                node->sprite = bSprite;
                node->model = model;
                
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
    
};



#endif /* LayoutEngine_h */
