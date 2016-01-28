//
//  CommonUtil.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#ifndef CommonUtil_hpp
#define CommonUtil_hpp

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE_TYPE "wav"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX )
#define MUSIC_FILE_TYPE "wav"
#else
#define MUSIC_FILE_TYPE "wav"
#endif

#include <stdio.h>
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace CocosDenshion;
USING_NS_CC;

class CommonUtil : public Ref {
    
public:
    static inline void playSoundWithName(__String* name)
    {
        __String* fileName = __String::createWithFormat("%s.%s",name->getCString(),MUSIC_FILE_TYPE);
        SimpleAudioEngine::getInstance()->playBackgroundMusic(fileName->getCString(),false);
    }
    static inline ParticleSystem* getParticleSystemForImageNameAndLayer(__String* imageName,Layer* layer)
    {
        ParticleSystem * p6=ParticleExplosion::create();
        p6->setTexture(Director::getInstance()->getTextureCache()->addImage(imageName->getCString()));
        p6->setAutoRemoveOnFinish(true);
        
        p6->setSpeed(100);
        p6->setSpeedVar(20);
        
        p6->setStartSize(10);
        p6->setStartSizeVar(5);
        p6->setEndSize(5);
        p6->setEndSizeVar(2);
        
        p6->setTotalParticles(5);
        p6->setDuration(1);
        p6->setLife(1.5);
        p6->setLifeVar(0.25);
        p6->setEmissionRate(60);
        
        return p6;
    }
    static inline Sprite* getBackSpriteForImageNameAndLayer(__String* imageName , Layer* layer)
    {
        Size contentSize = layer->getContentSize();
        Sprite* backImage = Sprite::create(imageName->getCString());
        
        backImage->setScaleX(.5);
        backImage->setScaleY(.5);
        
        return backImage;
    }
};

#endif /* CommonUtil_hpp */
