//
//  RootEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#include "RootEngine.hpp"
//初始化矩阵数据
void RootEngine::initStars()
{
    dataSource = CCArray::create();
    blocksInSameColor = CCArray::create();
    checkedBlocks = CCArray::create();
    allNodes = CCArray::create();
    allNodes->retain();
    dataSource->retain();
    blocksInSameColor->retain();
    checkedBlocks->retain();
    
    Size contentSize = containerView->getContentSize();
    perWidth = contentSize.width/lineCount;
    perHeight = perWidth;
    
    CCArray* nameArray = CCArray::create();
    for (int i = 0; i<typeCount; i++) {
        __String* s = __String::createWithFormat("img_star_%02d.png",i);
        nameArray->addObject(s);
    }
    
    for (int i = 0; i<lineCount; i++) {
        CCArray* lineArray = CCArray::create();
        dataSource->addObject(lineArray);
        for (int j = 0; j<rowCount; j++) {
            int type = arc4random()%typeCount;
            StarModel* model = new StarModel();
            model->type = type;
            model->line = i;
            model->row = j;
            lineArray->addObject(model);
            
            __String* file = (__String*)nameArray->objectAtIndex(model->type);
            Sprite* bSprite = Sprite::create(file->getCString());
            bSprite->setPosition(Point((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth));
            bSprite->setScale(CommonUtil::getScaleForTargetWithImage(perWidth, bSprite));
            containerView->addChild(bSprite);
            
            StarNode* node = new StarNode();
            node->sprite = bSprite;
            node->model = model;
            node->targetCenter = bSprite->getPosition();
            model->node = node;
            allNodes->addObject(node);
        }
    }
}


//获取点击ref周边相同颜色的ref
CCArray* RootEngine::getSameColorStarsWithStar(StarModel * model)
{
    blocksInSameColor->removeAllObjects();
    checkedBlocks->removeAllObjects();
    if (model == NULL) {
        return NULL;
    }
    // 执行递归。
    checkFourSides(model);
    return blocksInSameColor;
}


//获取对应位置上的model
StarModel* RootEngine::getModelForLineAndRow(int line,int row)
{
    if (line >= dataSource->count() || line < 0) {
        return NULL;
    }
    CCArray* array = (CCArray*)dataSource->objectAtIndex(line);
    for (int i = 0 ; i < array->count(); i++) {
        StarModel* model = (StarModel*)array->objectAtIndex(i);
        if (model->row == row) {
            return model;
        }
    }
    return NULL;
}

//判断游戏结束
bool RootEngine::checkDeath()
{
    if (allNodes->count()==0) {
        return true;
    }
    for (int i = 0; i<dataSource->count(); i++) {
        for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
            StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
            StarModel* blockUpside = this->getModelForLineAndRow(model->line+1, model->row);
            if (blockUpside !=NULL && blockUpside->type == model->type) {
                return false;
            }
            StarModel* blockDownside = this->getModelForLineAndRow(model->line-1, model->row);;
            if (blockDownside !=NULL && blockDownside->type == model->type) {
                return false;
            }
            StarModel* blockLeftside = this->getModelForLineAndRow(model->line, model->row-1);
            if (blockLeftside !=NULL && blockLeftside->type == model->type) {
                return false;
            }
            StarModel* blockRightside = this->getModelForLineAndRow(model->line, model->row+1);
            if (blockRightside !=NULL && blockRightside->type == model->type) {
                return false;
            }
        }
    }
    return true;
}

void RootEngine::clickPoint(Point p)
{
    int row = (p.y - containerView->getPosition().y) / this->perHeight;
    int line = (p.x - containerView->getPosition().x) / this->perWidth;
    StarModel* model = this->getModelForLineAndRow(line, row);
    CCArray* arr = blocksInSameColor;
    if (!arr || arr->count() == 0) {
        arr =  this->getSameColorStarsWithStar(model);
        this->highLightedSeltectedArray(blocksInSameColor);
    }else if (arr->containsObject(model)) {
        this->destroySlectedArray(blocksInSameColor,NULL);
        blocksInSameColor->removeAllObjects();
    }else {
        this->deHighLightedSelectedArray(blocksInSameColor);
        arr =  this->getSameColorStarsWithStar(model);
        this->highLightedSeltectedArray(blocksInSameColor);
    }
}

void RootEngine::highLightedSeltectedArray(CCArray* array)
{
    for (int i = 0; i < array->count(); i++) {
        StarModel* model = (StarModel*)array->objectAtIndex(i);
        StarNode* node = model->node;
        int type = model->type;
        __String* s = __String::createWithFormat("img_star_%02d_selected.png",type);
        node->sprite->setTexture(s->getCString());
    }
}

void RootEngine::deHighLightedSelectedArray(CCArray* array)
{
    for (int i = 0; i < array->count(); i++) {
        StarModel* model = (StarModel*)array->objectAtIndex(i);
        StarNode* node = model->node;
        int type = model->type;
        __String* s = __String::createWithFormat("img_star_%02d.png",type);
        node->sprite->setTexture(s->getCString());
    }
}

void RootEngine::destroySlectedArray(CCArray *array, makaCompleteCallback complete)
{
    if (array->count() == 0) {
        if (complete) {
            complete();
        }
        return;
    }
    
    completeCallback = complete;
    
    containerView->unscheduleAllCallbacks();
    for(int i = 0 ; i< array->count() ; i ++)
    {
        StarModel* model = (StarModel*)array->objectAtIndex(i);
        int line = model->line;
        CCArray* rowArray = (CCArray*)dataSource->objectAtIndex(line);
        rowArray->removeObject(model);
        allNodes->removeObject(model->node);
        
        Sprite* sp = model->node->sprite;
        containerView->scheduleOnce([sp,i,this](float dt){
            if (sp->isRunning()==false) {
                return ;
            }
            
            Point p = sp->getPosition();
            ParticleSystem* ps = CommonUtil::getParticleSystemForImageNameAndLayer(__String::create("star.png"),Color3B::ORANGE,perWidth/2);
            ps->setPosition(p);
            containerView->addChild(ps);
            
            sp->removeFromParent();
            if (i<=40) {
                CommonUtil::playSoundWithName(__String::create("pop"),0.8,0.8+i/16.0>1.5?1.5:0.8+i/16.0);
            }
            
            Point f = Point(p.x,p.y+perHeight);
            Point t = Point(containerView->getContentSize().width/2,containerView->getContentSize().height - 100);
            CommonUtil::createLabelMoveTo(f, t, __String::createWithFormat("%d",i*10+10),containerView);
            
        }, .1*i > 4 ? 4 :.1*i, __String::createWithFormat("random%d",i)->getCString());
    }
    
    containerView->scheduleOnce([array,this](float dt){
        CCArray* emptyArray = CCArray::create();
        
        for (int i = 0; i<dataSource->count(); i++) {
            CCArray* arr = (CCArray*)dataSource->objectAtIndex(i);
            
            if (arr->count() == 0) {
                emptyArray->addObject(arr);
            }
        }
        
        dataSource->removeObjectsInArray(emptyArray);
        
        for (int i = 0; i<dataSource->count(); i++) {
            for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
                StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
                model->line = i;
                model->row = j;
                StarNode* node = model->node;
                Point p = node->sprite->getPosition();
                Point t = ccp((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth);
                if (p.x != t.x || p.y != t.y) {
                    CCActionInterval * moveBy = CCMoveBy::create(0.3,Vec2(t.x-p.x, t.y-p.y));
                    CCActionInterval * actionmoveback= moveBy;
                    node->sprite->runAction(actionmoveback);
                }
            }
        }
        
        containerView->scheduleOnce([this](float dt){
            if (completeCallback) {
                completeCallback();
            }else{
                if (checkDeath()) {
                    death();
                }
            }
        }, 0.4, "delayClear");
        
    }, .1*array->count() > 4 ? 4 :array->count()*.1, "relayout");
}

void RootEngine::death()
{
    
}

void RootEngine::clearStars()
{
//    containerView->removeAllChildren();
//    dataSource->removeAllObjects();
//    blocksInSameColor->removeAllObjects();
//    allNodes->removeAllObjects();
//    checkedBlocks->removeAllObjects();
}


//判断上下左右
void RootEngine::checkFourSides(StarModel* model)
{
    if (checkedBlocks->containsObject(model)) {
        return;
    }else {
        checkedBlocks->addObject(model);
    }
    checkUp(model);
    checkDown(model);
    checkLeft(model);
    checkRight(model);
}

void RootEngine::checkUp(StarModel* model) {
    StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
    if (blockUpside ==NULL || blockUpside->type != model->type) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockUpside)) {
        blocksInSameColor->addObject(blockUpside);
    }
    this->checkFourSides(blockUpside);
}

void RootEngine::checkDown(StarModel* model){
    StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
    if (blockDownside ==NULL || blockDownside->type != model->type) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockDownside)) {
        blocksInSameColor->addObject(blockDownside);
    }
    this->checkFourSides(blockDownside);
}

void RootEngine::checkLeft(StarModel* model){
    StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
    if (blockLeftside ==NULL || blockLeftside->type != model->type) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockLeftside)) {
        blocksInSameColor->addObject(blockLeftside);
    }
    this->checkFourSides(blockLeftside);
}

void RootEngine::checkRight(StarModel* model){
    StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
    if (blockRightside ==NULL || blockRightside->type != model->type) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockRightside)) {
        blocksInSameColor->addObject(blockRightside);
    }
    this->checkFourSides(blockRightside);
}
