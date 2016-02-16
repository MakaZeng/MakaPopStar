//
//  ClassicEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/6.
//
//

#include "ClassicEngine.hpp"

void ClassicEngine::initStars()
{
    typeCount = 4;
    RootEngine::initStars();
}

void ClassicEngine::checkUp(StarModel* model) {
    StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
    if (blockUpside ==NULL || (blockUpside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockUpside)) {
        blocksInSameColor->addObject(blockUpside);
    }
    this->checkFourSides(blockUpside);
}

void ClassicEngine::checkDown(StarModel* model){
    StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
    if (blockDownside ==NULL || (blockDownside->type != model->type)){
        return;
    }
    if (!blocksInSameColor->containsObject(blockDownside)) {
        blocksInSameColor->addObject(blockDownside);
    }
    this->checkFourSides(blockDownside);
}

void ClassicEngine::checkLeft(StarModel* model){
    StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
    if (blockLeftside ==NULL || (blockLeftside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockLeftside)) {
        blocksInSameColor->addObject(blockLeftside);
    }
    this->checkFourSides(blockLeftside);
}

void ClassicEngine::checkRight(StarModel* model){
    StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
    if (blockRightside ==NULL || (blockRightside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockRightside)) {
        blocksInSameColor->addObject(blockRightside);
    }
    this->checkFourSides(blockRightside);
}


void ClassicEngine::death()
{
    
    CCArray* arr = CCArray::create();
    for (int i = 0; i<allNodes->count(); i++) {
        StarNode* starNode = (StarNode*)allNodes->objectAtIndex(i);
        arr->addObject(starNode->model);
    }
    destroySlectedArray(arr,[this](){
        clearStars();
        initStars();
    });
}







