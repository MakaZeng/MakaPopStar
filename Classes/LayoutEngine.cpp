//
//  LayoutEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#include <stdio.h>
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
#include "PopStarCore.cpp"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#define MUSIC_FILE        "tap.wav"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )

#define MUSIC_FILE        "tap.wav"

#else

#define MUSIC_FILE        "tap.wav"

#endif


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
    Layer* cacheLayer;
    
public:
    
    void layoutStarsWithDataSourceAndLayer(CCArray* dataSource , Layer* layer)
    {
        cacheLayer = layer;
        
        layer->removeAllChildren();
        
        allNodes = CCArray::create();
        allNodes->retain();
        
        Rect rect = layer->getBoundingBox();
        
        perWidth = rect.size.width/10;
        perHeight = perWidth;
        
        CCArray* nameArray = CCArray::create();
        
        String* blue = String::create("image_00.png");
        String* green = String::create("image_01.png");
        String* orange = String::create("image_02.png");
        String* purple = String::create("image_03.png");
        String* red = String::create("image_04.png");
        
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
                
                bSprite->setPosition(ccp((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth + Director::sharedDirector()->getVisibleSize().height));
                
                CCActionInterval * moveBy = CCMoveBy::create(1+i*.1+j*.1,Vec2(0, 0 - Director::sharedDirector()->getVisibleSize().height));
                bSprite->runAction(moveBy);
                
                model->line = i;
                model->row = j;
                
                bSprite->setScale(0.1,0.1);
                
                //                auto body = PhysicsBody::createBox(Size(bSprite->getContentSize().width+5, bSprite->getContentSize().height+5));
                //                bSprite->setPhysicsBody(body);
                //
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
            
            cacheLayer->scheduleOnce([sp,this](float){
                //CCParticleMeteor特效
                if (!sp->isRunning()) {
                    return ;
                }
                CCParticleSystem * p6=CCParticleExplosion::create();
                p6->setTexture(CCTextureCache::sharedTextureCache()->addImage("ParticleStar.png"));
                p6->setSpeed(100);
                p6->setSpeedVar(20);
                p6->setStartSize(50);
                p6->setStartSizeVar(5);
                p6->setEndSize(10);
                p6->setEndSizeVar(2);
                p6->setAutoRemoveOnFinish(true);
                p6->setAngle(360);
                p6->setPosition(sp->getPosition());
                p6->setPositionType(kCCPositionTypeFree);
                p6->setTotalParticles(5);
                p6->setDuration(1);
                p6->setLife(1.5);
                p6->setLifeVar(0.25);
                p6->setEmissionRate(60);
                p6->setEmitterMode(kCCParticleModeGravity);
                
                p6->setStartColor( ccc4f(200/255.0, 0/255.0, 0/255.0, 255/255.0) );
                p6->setStartColorVar( ccc4f(0, 0, 0, 0) );
                p6->setEndColor( ccc4f(0, 0, 0, 0) );
                p6->setEndColorVar( ccc4f(0, 0, 0, 0) );
                
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,false);
                cacheLayer->addChild(p6);
                cacheLayer->removeChild(sp);
            }, i*0.2, String::createWithFormat("Part%d",i) ->getCString());
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



#endif /* LayoutEngine_h */
