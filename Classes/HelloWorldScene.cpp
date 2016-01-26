#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
//    auto rootNode = CSLoader::createNode("MainScene.csb");

//    addChild(rootNode);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto backLayer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    addChild(backLayer);
    
    containerLayer = LayerColor::create(Color4B::WHITE, visibleSize.width-40, visibleSize.height-40);
    containerLayer->setPosition(20, 20);
    addChild(containerLayer);
    
    
    manager->initStars();
    
    engine->layoutStarsWithDataSourceAndLayer(manager->dataSource, containerLayer);
    {
        auto listener1 = EventListenerTouchOneByOne::create();
        listener1->setSwallowTouches(true);
        listener1->onTouchBegan = [this](Touch* touch, Event* event){
            // 获取事件所绑定的 target
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            
            // 获取当前点击点所在相对按钮的位置坐标
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            // 点击范围判断检测
            if (rect.containsPoint(locationInNode))
            {
                this->touchPoint(locationInNode);
                return true;
            }
            return false;
        };
        
        // 触摸移动时触发
        listener1->onTouchMoved = [](Touch* touch, Event* event){};
        
        // 点击事件结束处理
        listener1->onTouchEnded = [](Touch* touch, Event* event){};
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, containerLayer);

    }
    

    return true;
}

void HelloWorld::touchPoint(Point point)
{
    Point modelPoint = engine->getClickStarModelPointWith(point);
    StarModel* model = manager->getModelForLineAndRow(modelPoint.x, modelPoint.y);
    if (model!=NULL) {
        CCArray* list = manager->getSameColorStarsWithStar(model);
        for(int i = 0 ; i< list->count() ; i++)
        {
            StarModel* s = (StarModel*)list->objectAtIndex(i);
            log("%d,%d",s->line,s->row);
        }
        manager->destroyStars(list);
        
        engine->layoutStarsWithDataSourceAndLayer(manager->dataSource, containerLayer);
    }
}

