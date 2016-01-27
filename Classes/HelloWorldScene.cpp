#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::extension;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(body);
    addChild(edgeNode);
    
    
    auto backLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    addChild(backLayer);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);
    
    //设置默认音量
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.03);
    
    Sprite* backImage = Sprite::create("sky.jpg");
    backImage->setPosition(Point(backImage->getContentSize().width/2,backImage->getContentSize().height/2));
    addChild(backImage);
    
    containerLayer = Layer::create();
    containerLayer->setPosition(0, 80);
    Size containerSize = containerLayer->getContentSize();
    auto containerBody = PhysicsBody::createEdgeBox(containerSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    auto containerEdgeNode = Node::create();
    containerEdgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    containerEdgeNode->setPhysicsBody(containerBody);
    addChild(containerEdgeNode);
    
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
    static bool lock = false;
    
    if (lock) {
        return;
    }
    lock = true;
    Point modelPoint = engine->getClickStarModelPointWith(point);
    StarModel* model = manager->getModelForLineAndRow(modelPoint.x, modelPoint.y);
    if (model!=NULL) {
        CCArray* list = manager->getSameColorStarsWithStar(model);
        for(int i = 0 ; i< list->count() ; i++)
        {
            StarModel* s = (StarModel*)list->objectAtIndex(i);
            log("%d,%d,%p",s->line,s->row,s);
        }
        if (list->count() >= 2) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,false);
        }
        manager->destroyStars(list);
        engine->removeStars(list);
        scheduleOnce([this](float){
            engine->relayout(manager->dataSource);
        }, 0.2*list->count(), "pop");
    }
    
    if (manager->checkDeath()) {
        manager->initStars();
        engine->layoutStarsWithDataSourceAndLayer(manager->dataSource, containerLayer);
    }
    
    scheduleOnce([](float){
        lock = false;
    }, 0.5, "key");
}

