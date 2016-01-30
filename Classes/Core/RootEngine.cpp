//
//  RootEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/1/30.
//
//

#include "RootEngine.hpp"
#include "ScreenUtil.hpp"
#include "CommonUtil.hpp"

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

//摧毁某些Stars
void RootEngine::destroyStars(CCArray * stars)
{
    if (stars->count() == 0) {
        return;
    }
    for(int i = 0 ; i< stars->count() ; i ++)
    {
        StarModel* model = (StarModel*)stars->objectAtIndex(i);
        int line = model->line;
        CCArray* rowArray = (CCArray*)dataSource->objectAtIndex(line);
        rowArray->removeObject(model);
    }
    if (checkDeath()) {
    }
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



void RootEngine::layoutStars()
{
    Size contentSize = containerView->getContentSize();
    perWidth = contentSize.width/15;
    perHeight = perWidth;
    
    CCArray* nameArray = CCArray::create();
    for (int i = 0; i<5; i++) {
        __String* s = __String::createWithFormat("image_0%d.png",i);
        nameArray->addObject(s);
    }
    
    Size screenSize = ScreenUtil::getBestScreenSize();
    
    for (int i = 0; i<dataSource->count(); i++) {
        for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
            StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
            model->line = i;
            model->row = j;
            
            __String* file = (__String*)nameArray->objectAtIndex(model->type);
            Sprite* bSprite = Sprite::create(file->getCString());
            bSprite->setPosition(Point((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth + screenSize.height));
            bSprite->setScale(CommonUtil::getScaleForTargetWithImage(perWidth, bSprite));
            containerView->addChild(bSprite);
            
            StarNode* node = new StarNode();
            node->sprite = bSprite;
            node->model = model;
            node->targetCenter = bSprite->getPosition();
            allNodes->addObject(node);
        }
    }
}


Point RootEngine::getClickStarModelPointWith(Point p)
{
    int row = p.y / this->perHeight;
    int line = p.x / this->perWidth;
    
    return Vec2(line, row);
}

Sprite* RootEngine::getRelatedSpriteWith(StarModel* model)
{
    for(int i = 0 ; i < allNodes->count() ; i ++)
    {
        StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
        if (n->model == model) {
            return n->sprite;
        }
    }
    return NULL;
}

StarNode* RootEngine::getNodeForModel(StarModel* model)
{
    for(int i = 0 ; i < allNodes->count() ; i ++)
    {
        StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
        if (n->model == model) {
            return n;
        }
    }
    return NULL;
}

void RootEngine::removeNodeForModel(StarModel* model)
{
    for(int i = 0 ; i < allNodes->count() ; i ++)
    {
        StarNode* n = (StarNode*)allNodes->objectAtIndex(i);
        if (n->model == model) {
            allNodes->removeObject(n);
            return;
        }
    }
}

void RootEngine::removeStars(CCArray* stars)
{
    containerView->unscheduleAllCallbacks();
    for(int i = 0 ; i < stars->count() ; i ++)
    {
        StarModel* model = (StarModel*)stars->objectAtIndex(i);
        Sprite* sp = getRelatedSpriteWith(model);
        
        
        containerView->scheduleOnce([sp,i,this](float dt){
            
            if (sp->isRunning()==false) {
                return ;
            }
            
            Point p = sp->getPosition();
            ParticleSystem* ps = CommonUtil::getParticleSystemForImageNameAndLayer(__String::create("star.png"),Color3B::ORANGE,perWidth/2);
            ps->setPosition(p);
            containerView->addChild(ps);
            
            sp->removeFromParent();
            if (i<=50) {
                CommonUtil::playSoundWithName(__String::create("pop"),0.8,0.8+i/16.0>1.5?1.5:0.8+i/16.0);
            }
            
            Point f = Point(p.x,p.y+perHeight);
            Point t = Point(containerView->getContentSize().width/2,containerView->getContentSize().height - 100);
            CommonUtil::createLabelMoveTo(f, t, __String::createWithFormat("%d",i*10+10),containerView);
            
        }, .05*i > 10 ? 10 :.05*i, __String::createWithFormat("random%d",i)->getCString());
        
        removeNodeForModel(model);
    }
}

void RootEngine::relayout(CCArray* dataSource)
{
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
            
            StarNode* node = getNodeForModel(model);
            
            Point p = node->sprite->getPosition();
            Point t = ccp((i+ 0.5)*this->perHeight, (j+0.5)*this->perWidth);
            
            if (p.x != t.x || p.y != t.y) {
                CCActionInterval * moveBy = CCMoveBy::create(0.3,Vec2(t.x-p.x, t.y-p.y));
                CCActionInterval * actionmoveback= moveBy;
                node->sprite->runAction(actionmoveback);
                allNodes->addObject(node);
            }
            
        }
    }
    
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
