//
//  PopStarCore.h
//  MakaPopStar
//
//  Created by Maka on 26/1/16.
//
//

#ifndef PopStarCore_h
#define PopStarCore_h

#include "cocos2d.h"

using namespace cocos2d;

class StarModel : public Ref {
public:
    int line;
    int row;
    int type;
    
public:
    
};


class MatrixManager : public Ref {
    
public:
    
    int typeCount = 5;
    int lineCount = 10;
    int rowCount = 10;
    
    Node* starContainer;
    
    CCArray* dataSource;
    
    CCArray* checkedBlocks;
    CCArray* blocksInSameColor;
    
public:
    
    //获取点击ref周边相同颜色的ref
    CCArray* getSameColorStarsWithStar(StarModel * model)
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
    
    //摧毁某些ref
    void destroyStars(CCArray * stars)
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
    }
    
    
    //获取对应位置上的model
    StarModel* getModelForLineAndRow(int line,int row)
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
    bool checkDeath()
    {
        for (int i = 0; i<dataSource->count(); i++) {
            for (int j = 0; j<((CCArray*)dataSource->objectAtIndex(i))->count(); j++) {
                StarModel* model = (StarModel*)((CCArray*)dataSource->objectAtIndex(i))->objectAtIndex(j);
                StarModel* blockUpside = this->getModelForLineAndRow(model->line+1, model->row);
                if (blockUpside ==NULL && blockUpside->type == model->type) {
                    return false;
                }
                StarModel* blockDownside = this->getModelForLineAndRow(model->line-1, model->row);;
                if (blockDownside ==NULL && blockDownside->type == model->type) {
                    return false;
                }
                StarModel* blockLeftside = this->getModelForLineAndRow(model->line, model->row-1);
                if (blockLeftside ==NULL && blockLeftside->type == model->type) {
                    return false;
                }
                StarModel* blockRightside = this->getModelForLineAndRow(model->line, model->row+1);
                if (blockRightside ==NULL && blockRightside->type == model->type) {
                    return false;
                }
            }
        }
        return true;
    }

    //初始化矩阵数据
    void initStars()
    {
        dataSource = CCArray::create();
        blocksInSameColor = CCArray::create();
        checkedBlocks = CCArray::create();
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
    
    //判断上下左右
    void checkFourSides(StarModel* model)
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
    
    void checkUp(StarModel* model) {
        StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
        if (blockUpside ==NULL || blockUpside->type != model->type) {
            return;
        }
        blocksInSameColor->addObject(blockUpside);
        this->checkFourSides(blockUpside);
    }
    
    void checkDown(StarModel* model){
        StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
        if (blockDownside ==NULL || blockDownside->type != model->type) {
            return;
        }
        blocksInSameColor->addObject(blockDownside);
        this->checkFourSides(blockDownside);
    }
    
    void checkLeft(StarModel* model){
        StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
        if (blockLeftside ==NULL || blockLeftside->type != model->type) {
            return;
        }
        blocksInSameColor->addObject(blockLeftside);
        this->checkFourSides(blockLeftside);
    }
    
    void checkRight(StarModel* model){
        StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
        if (blockRightside ==NULL || blockRightside->type != model->type) {
            return;
        }
        blocksInSameColor->addObject(blockRightside);
        this->checkFourSides(blockRightside);
    }

    
};



#endif /* PopStarCore_h */
