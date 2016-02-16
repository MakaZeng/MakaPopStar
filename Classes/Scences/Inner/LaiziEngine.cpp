//
//  LaiziEngine.cpp
//  MakaPopStar
//
//  Created by chaowualex on 16/2/1.
//
//

#include "LaiziEngine.hpp"

void LaiziEngine::initStars()
{
    typeCount = 2;
    RootEngine::initStars();
}

void LaiziEngine::checkUp(StarModel* model) {
    StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
    if (blockUpside ==NULL || (blockUpside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockUpside)) {
        blocksInSameColor->addObject(blockUpside);
    }
    this->checkFourSides(blockUpside);
}

void LaiziEngine::checkDown(StarModel* model){
    StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
    if (blockDownside ==NULL || (blockDownside->type != model->type)){
        return;
    }
    if (!blocksInSameColor->containsObject(blockDownside)) {
        blocksInSameColor->addObject(blockDownside);
    }
    this->checkFourSides(blockDownside);
}

void LaiziEngine::checkLeft(StarModel* model){
    StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
    if (blockLeftside ==NULL || (blockLeftside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockLeftside)) {
        blocksInSameColor->addObject(blockLeftside);
    }
    this->checkFourSides(blockLeftside);
}

void LaiziEngine::checkRight(StarModel* model){
    StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
    if (blockRightside ==NULL || (blockRightside->type != model->type)) {
        return;
    }
    if (!blocksInSameColor->containsObject(blockRightside)) {
        blocksInSameColor->addObject(blockRightside);
    }
    this->checkFourSides(blockRightside);
}
