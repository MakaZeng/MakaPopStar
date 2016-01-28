//
//  ScreenUtil.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/27.
//
//

#ifndef ScreenUtil_hpp
#define ScreenUtil_hpp

#include <stdio.h>

USING_NS_CC;

class ScreenUtil : public cocos2d::Ref {
    
public:
    static inline Size getBestScreenSize()
    {
        Size size = Director::getInstance()->getVisibleSize();
        return size;
    }
};


#endif /* ScreenUtil_hpp */
