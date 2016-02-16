//
//  DaojuEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#include "DaojuEngine.hpp"
#include "CommonUtil.hpp"

void DaojuEngine::initStars()
{
    typeCount = 5;
    RootEngine::initStars();
}

void DaojuEngine::checkUp(StarModel* model) {
    StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
    if (blockUpside ==NULL || (blockUpside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockUpside)) {
        blocksInSameColor->addObject(blockUpside);
    }
    this->checkFourSides(blockUpside);
}

void DaojuEngine::checkDown(StarModel* model){
    StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
    if (blockDownside ==NULL || (blockDownside->type != model->type)){
        return;
    }
    if (!blocksInSameColor->containsObject(blockDownside)) {
        blocksInSameColor->addObject(blockDownside);
    }
    this->checkFourSides(blockDownside);
}

void DaojuEngine::checkLeft(StarModel* model){
    StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
    if (blockLeftside ==NULL || (blockLeftside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockLeftside)) {
        blocksInSameColor->addObject(blockLeftside);
    }
    this->checkFourSides(blockLeftside);
}

void DaojuEngine::checkRight(StarModel* model){
    StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
    if (blockRightside ==NULL || (blockRightside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockRightside)) {
        blocksInSameColor->addObject(blockRightside);
    }
    this->checkFourSides(blockRightside);
}


void DaojuEngine::daoJuHitPoint(Point p, int type){
    int row = p.y / this->perHeight;
    int line = p.x / this->perWidth;
    StarModel* model = this->getModelForLineAndRow(line, row);
    if (!model) {
        return;
    }
    switch (type) {
        case 0:
        {
            break;
        }
        default:
            break;
    }
}


void DaojuEngine::daoJuConfirmHitPoint(Point p, int type){
    int row = p.y / this->perHeight;
    int line = p.x / this->perWidth;
    StarModel* model = this->getModelForLineAndRow(line, row);
    if (!model) {
        return;
    }
    switch (type) {
        case 0:
        {
            model->type = 2;
            model->node->sprite->setTexture("image_02.png");
            break;
        }
        case 1:
        {
            CCArray* arr = CCArray::create();
            arr->addObject(model);
            destroySlectedArray(arr,NULL);
            break;
        }
        case 2:
        {
            CCArray* arr = CCArray::create();
            arr->addObject(model);
            StarModel* block = getModelForLineAndRow(model->line-1, model->row);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line+1, model->row);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line, model->row-1);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line, model->row+1);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line-1, model->row-1);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line+1, model->row+1);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line+1, model->row-1);
            if (block) {
                arr->addObject(block);
            }
            block = getModelForLineAndRow(model->line-1, model->row+1);
            if (block) {
                arr->addObject(block);
            }
            destroySlectedArray(arr,NULL);
            break;
        }
        case 3:
        {
            CCArray* nameArray = CCArray::create();
            for (int i = 0; i<5; i++) {
                __String* s = __String::createWithFormat("image_0%d.png",i);
                nameArray->addObject(s);
            }
            
            for (int i = 0; i<dataSource->count(); i++) {
                CCArray* lineArr = (CCArray*)dataSource->objectAtIndex(i);
                for (int j = 0; j<lineArr->count(); j++) {
                    StarModel* model = getModelForLineAndRow(i, j);
                    
                    int type = arc4random()%typeCount;
                    model->type = type;
                    model->line = i;
                    model->row = j;
                    
                    __String* file = (__String*)nameArray->objectAtIndex(model->type);
                    Sprite* bSprite = model->node->sprite;
                    bSprite->setTexture(file->getCString());
                }
            }
            
            break;
        }
        case 4:
        {
            for (int i = 0; i<dataSource->count(); i++) {
                CCArray* lineArr = (CCArray*)dataSource->objectAtIndex(i);
                for (int j = 0; j<lineArr->count(); j++) {
                    StarModel* model = getModelForLineAndRow(i, j);
                    if (!model) {
                        return;
                    }
                    int tLine = arc4random()%dataSource->count();
                    int tRow = arc4random()%(((CCArray*)dataSource->objectAtIndex(tLine))->count());
                    
                    StarModel* tModel = getModelForLineAndRow(tLine, tRow);
                    if (!tModel) {
                        return;
                    }
                    
                    CCArray* TEMP = NULL;
                    
                    if (tModel) {
                        
                        TEMP = (CCArray*)dataSource->objectAtIndex(model->line);
                        TEMP->removeObjectAtIndex(model->row);
                        TEMP->insertObject(tModel, model->row);
                        
                        TEMP = (CCArray*)dataSource->objectAtIndex(tModel->line);
                        TEMP->removeObjectAtIndex(tModel->row);
                        TEMP->insertObject(model, tModel->row);
                        
                        
                        int temp = model->line;
                        model->line = tModel->line;
                        tModel->line = temp;
                        
                        temp = model->row;
                        model->row = tModel->row;
                        tModel->row = temp;
                        
                    }
                }
            }
            
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
                        allNodes->addObject(node);
                    }
                }
            }
            
            
            break;
        }
        default:
            break;
    }
}


