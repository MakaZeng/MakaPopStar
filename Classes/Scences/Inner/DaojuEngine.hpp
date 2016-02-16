//
//  DaojuEngine.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#ifndef DaojuEngine_hpp
#define DaojuEngine_hpp

#include <stdio.h>
#include "RootEngine.hpp"

class DaojuEngine: public RootEngine {
public:
    void checkUp(StarModel* model);
    void checkDown(StarModel* model);
    void checkLeft(StarModel* model);
    void checkRight(StarModel* model);
    void initStars();
    
    void daoJuHitPoint(Point p , int type);
    void daoJuConfirmHitPoint(Point p , int type);
};

#endif /* DaojuEngine_hpp */
