//
//  LaiziEngine.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/1.
//
//

#ifndef LaiziEngine_hpp
#define LaiziEngine_hpp

#include <stdio.h>
#include "RootEngine.hpp"

class LaiziEngine : public RootEngine {
public:
    void checkUp(StarModel* model);
    void checkDown(StarModel* model);
    void checkLeft(StarModel* model);
    void checkRight(StarModel* model);
    void initStars();
};

#endif /* LaiziEngine_hpp */
