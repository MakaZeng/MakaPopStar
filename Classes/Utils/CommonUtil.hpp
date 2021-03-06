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

#define FONT_NAME "Verdana"
#define FONT_SIZE 28

#define TOP_TOOLBAR_HEIGHT 80

using namespace CocosDenshion;
USING_NS_CC;
using namespace cocos2d::ui;

class CommonUtil : public Ref {
    
public:
    static inline void playSoundWithName(__String* name,float volume,float pitch)
    {
        __String* fileName = __String::createWithFormat("%s.%s",name->getCString(),MUSIC_FILE_TYPE);
        SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
        SimpleAudioEngine::getInstance()->playEffect(fileName->getCString(),false,pitch);
    }
    static inline ParticleSystem* getParticleSystemForImageNameAndLayer(__String* imageName,Color3B color = Color3B::RED   ,float size = 10)
    {
        ParticleSystem * p6=ParticleExplosion::create();
        p6->setTexture(Director::getInstance()->getTextureCache()->addImage(imageName->getCString()));
        p6->setAutoRemoveOnFinish(true);
        
        p6->setSpeed(100);
        p6->setSpeedVar(20);
        
        p6->setStartSize(size);
        p6->setStartSizeVar(50);
        p6->setEndSize(5);
        p6->setEndSizeVar(2);
        
        p6->setTotalParticles(5);
        p6->setDuration(1);
        p6->setLife(1.5);
        p6->setLifeVar(0.25);
        p6->setEmissionRate(60);
        
        p6->setColor(color);
        
        return p6;
    }
    
    static inline void getTailImageSpriteWithImageName(__String* s , Layer* layer , bool random)
    {
        
        Size contentSize = layer->getContentSize();
        
        Sprite* image ;
        
        if (random) {
            image = Sprite::create(__String::createWithFormat("%s_0.png",s->getCString())->getCString());
        }else {
            image = Sprite::create(s->getCString());
        }
        
        Size imageSize = image->getTextureRect().size;
        
        Sprite* sp;
        
        int tailLine = contentSize.width/imageSize.width+1;
        int tailRow = contentSize.height/imageSize.height+1;
        
        float totalWidth = tailLine*imageSize.width;
        float totalHeight = tailRow*imageSize.height;
        
        float leftPadding = (totalWidth-contentSize.width)/2;
        float bottomPadding = (totalHeight-contentSize.height)/2;
        
        for(int i=0;i<tailLine;i++)
        {
            for(int j=0;j<tailRow;j++)
            {
                if (random) {
                    sp = Sprite::create(__String::createWithFormat("%s_%d.png",s->getCString(),((int)(CCRANDOM_0_1()*100))%7)->getCString());
                }else {
                    sp = Sprite::create(s->getCString());
                }
                
                sp->setAnchorPoint(Point(0,0));
                sp->setPosition(Point(imageSize.width*i - leftPadding,imageSize.height*j - bottomPadding));
                if(i%2==0)
                {
                    sp->setFlippedX(true);
                }
                layer->addChild(sp);
            }
        }    
        return;
    }
    
    static inline Sprite* getBackSpriteForImageNameAndLayer(__String* imageName , Layer* layer)
    {
        Size contentSize = layer->getContentSize();
        
        if (contentSize.width/contentSize.height > contentSize.height/contentSize.width) {
            //替换成对应的横屏图
        }
        
        Sprite* backImage = Sprite::create(imageName->getCString());
        
        backImage->setAnchorPoint(Point(0,0));
        
        Size textureSize = backImage->getTextureRect().size;
        
        float scale;
        
        if (contentSize.width/contentSize.height < textureSize.width/textureSize.height) {
            scale = contentSize.height/textureSize.height;
        }else {
            scale = contentSize.width/textureSize.width;
        }
        
        scale = 1;

        backImage->setScaleX(scale);
        backImage->setScaleY(scale);
        
        return backImage;
    }
    static Sprite* runRoundSpriteWithImageName(__String* imageName , float time)
    {
        Sprite* image = Sprite::create(imageName->getCString());
        ActionInterval * rotate = RotateTo::create(time/2,180);
        ActionInterval * rotate2 = RotateTo::create(time/2,360);
        FiniteTimeAction* seq = Sequence::create(rotate,rotate2,NULL);
        ActionInterval * repeatForever =RepeatForever::create((ActionInterval* )seq);
        image->runAction(repeatForever);
        
        return image;
    }
    static Sprite* moveUp(float offset , Point start , __String* imageName , float time)
    {
        Sprite* image = Sprite::create(imageName->getCString());
        
        image->setPosition(start);
        
        ActionInterval * move = MoveTo::create(time,Vec2(start.x, start.y+offset));
        image->runAction(move);
        
        return image;
    }
    
    static void addRepeatForeverShake(Sprite* sp){
        ActionInterval * rotate = RotateTo::create(.1,10);
        ActionInterval * rotate2 = RotateTo::create(.2,-10);
        ActionInterval * rotate3 = RotateTo::create(.1,0);
        ActionInterval * sleep = RotateTo::create(5,0);
        FiniteTimeAction* seq = Sequence::create(rotate,rotate2,rotate3,rotate,rotate2,rotate3,sleep,NULL);
        ActionInterval * repeatForever =RepeatForever::create((ActionInterval* )seq);
        sp->runAction(repeatForever);
    }
    
    static void addEaseZoonIn(Sprite* sp){
        sp->setScale(.1);
        ActionInterval * scaleby = ScaleTo::create(1, 1);
        sp->runAction(scaleby);
    }
    
    static Button* buttonForBackImageAndContent(__String* imageName,__String* content)
    {
        Button* buttonPlay = Button::create();
        buttonPlay->setTouchEnabled(true);
        buttonPlay->setTitleText(content->getCString());
        buttonPlay->loadTextures(imageName->getCString(), imageName->getCString(), "");
        return buttonPlay;
    }
    
    static float getScaleForTargetWithImage(float t , Sprite* image)
    {
        Size textureSize = image->getTextureRect().size;
        
        return getScaleForTargetWithCurrent(t, textureSize.width);
    }
    
    static float getScaleForTargetWithCurrent(float t , float c){
        return t/c;
    }
    
    static Layer* createToolBarForWidthAndHeight(float width , float height)
    {
        Layer* layer = Layer::create();
        
        layer->setContentSize(Size(width, height));
        
        Sprite* sp = Sprite::create("star.png");
        sp->setScale(width/5, height/5);
        sp->cocos2d::Node::setAnchorPoint(Point(0,0));
        layer->addChild(sp);
        return layer;
    }
    
    static Label* createLabelMoveTo(Point f, Point t , __String* text,Layer* container)
    {
        Label* label=Label::createWithSystemFont(text->getCString(), "Arial", 50);
        label->setPosition(f);
        label->setTextColor(Color4B::WHITE);
        auto moveTo = MoveTo::create(1, t);
        label->runAction(moveTo);
        
        ActionInterval * hide = FadeOut::create(1);
        
        Spawn* seq = Spawn::createWithTwoActions(moveTo, hide);
        
        label->runAction(seq);
        
        container->addChild(label);
    }
};

#endif /* CommonUtil_hpp */
