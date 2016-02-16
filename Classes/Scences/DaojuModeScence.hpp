//
//  DaojuModeScence.hpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#ifndef DaojuModeScence_hpp
#define DaojuModeScence_hpp

#include <stdio.h>
#include "DaojuEngine.hpp"
#include "DaojuModeTopTool.hpp"
#include "GamePlayRootScence.hpp"

class DaojuModeScence : public GamePlayRootScence {
public:
    CREATE_FUNC(DaojuModeScence);
    static Scene* createScene();
    virtual bool init();
    DaojuEngine* engine;
    DaojuModeTopTool* topTool;
    virtual void clickPoint(Point p);
    
    bool usingDaoju = false;
};

#endif /* DaojuModeScence_hpp */
