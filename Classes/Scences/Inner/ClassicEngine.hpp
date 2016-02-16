//
//  ClassicEngine.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#ifndef ClassicEngine_hpp
#define ClassicEngine_hpp

#include <stdio.h>
#include "CommonUtil.hpp"
#include "ScreenUtil.hpp"
#include "RootEngine.hpp"

class ClassicEngine :public RootEngine {
public:
    void checkUp(StarModel* model);
    void checkDown(StarModel* model);
    void checkLeft(StarModel* model);
    void checkRight(StarModel* model);
    void initStars();
    virtual void death();
};

#endif /* ClassicEngine_hpp */
