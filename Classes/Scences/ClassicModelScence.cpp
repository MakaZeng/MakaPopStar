//
//  ClassicModelScence.cpp
//  MakaPopStar
//
//  Created by Maka on 28/1/16.
//
//

#include "ClassicModelScence.hpp"

Scene* ClassicModelScence::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ClassicModelScence::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ClassicModelScence::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->preloadEffect("pop.wav");
    
    Size contentSize = ScreenUtil::getBestScreenSize();
    
    Layer* toolBar = CommonUtil::createToolBarForWidthAndHeight(contentSize.width, contentSize.height);
    
    toolBar->setAnchorPoint(Point(0,0));
    
    toolBar->setPosition(Point(0,0));
    
    addChild(toolBar);
    
    Layer* starsContainer = Layer::create();
    
    float padding = 40;
    
    starsContainer->setContentSize(Size(contentSize.width - padding , contentSize.height - padding));
    
    starsContainer->setAnchorPoint(Point(0,0));
    
    starsContainer->setPosition(Point(padding/2,padding/2));
    
    addChild(starsContainer);
    
    MatrixManager* core = new MatrixManager();
    
    core->initStars();
    
    LayoutEngine* engine = new LayoutEngine();
    
    engine->retain();
    
    engine->layoutStarsWithDataSourceAndLayer(core->dataSource, starsContainer);
    
    this->control = ClassicModelControl::create();
    control->setContentSize(Size(contentSize.width,100));
    control->setAnchorPoint(Point(0,0));
    control->setPosition(Point(0,contentSize.height-100));
    
    engine->classicControl = control;
    
    Size controlSize = control->getContentSize();
    
    auto listenter = EventListenerTouchOneByOne::create();
    listenter->onTouchBegan = [starsContainer,engine,core,this](Touch* t, Event * e) {
        if (starsContainer->getBoundingBox().containsPoint(t->getLocation())) {
            Point p =  engine->getClickStarModelPointWith(t->getLocation());
            StarModel* model = core->getModelForLineAndRow(p.x, p.y);
            if (model) {
                CCArray* arr = core->getSameColorStarsWithStar(model);
                core->destroyStars(arr);
                engine->removeStars(arr);
                starsContainer->scheduleOnce([engine,core,arr,this](float dt){
                    engine->relayout(core->dataSource);
                }, .2*arr->count() > 10 ? 10 :.2*arr->count(), "pop");
            }
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenter, starsContainer);
    
    addChild(control);
    
    return true;
}