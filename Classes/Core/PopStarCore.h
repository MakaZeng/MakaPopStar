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
    
    int typeCount;
    int lineCount;
    int rowCount;
    
    Node* starContainer;
    
    Vector<Vector<StarModel *> *> * dataSource;
    
    Vector<StarModel *> * checkedBlocks;
    Vector<StarModel *> * blocksInSameColor;
    
public:
    
    //获取点击ref周边相同颜色的ref
    Vector<StarModel *> * getSameColorStarsWithStar(StarModel * model)
    {
        if (model == NULL) {
            return NULL;
        }
        
        // 执行递归。
        checkFourSides(model);
        return blocksInSameColor;
    }
    
    //摧毁某些ref
    void destroyStars(Vector<StarModel *> * stars)
    {
        if (stars->size() == 0) {
            return;
        }
        
        for(StarModel* model : *stars)
        {
            int line = model->line;
            Vector<StarModel *> * rowArray = dataSource->at(line);
            rowArray->eraseObject(model);
        }
    }
    
    
    //获取对应位置上的model
    StarModel* getModelForLineAndRow(int line,int row)
    {
        if (line >= dataSource->size() || line < 0) {
            return NULL;
        }
        Vector<StarModel *> * array = dataSource->at(line);
        
        for (int i = 0 ; i < array->size(); i++) {
            StarModel* model = (StarModel*)array->at(i);
            if (model->row == row) {
                return model;
            }
        }
        return NULL;
    }
    
    //判断游戏结束
    bool checkDeath()
    {
        for (int i = 0; i<dataSource->size(); i++) {
            for (int j = 0; j<((Vector<StarModel *> *)dataSource->at(i))->size(); j++) {
                StarModel* model = (StarModel*)((Vector<StarModel *> *)dataSource->at(i))->at(j);
                StarModel* blockUpside = this->getModelForLineAndRow(model->line+1, model->row);
                if (blockUpside != NULL && blockUpside->type == model->type) {
                    return false;
                }
                StarModel* blockDownside = this->getModelForLineAndRow(model->line-1, model->row);;
                if (blockDownside != NULL && blockDownside->type == model->type) {
                    return false;
                }
                StarModel* blockLeftside = this->getModelForLineAndRow(model->line, model->row-1);
                if (blockLeftside != NULL && blockLeftside->type == model->type) {
                    return false;
                }
                StarModel* blockRightside = this->getModelForLineAndRow(model->line, model->row+1);
                if (blockRightside != NULL && blockRightside->type == model->type) {
                    return false;
                }
            }
        }
        return true;
    }

    //初始化矩阵数据
    void initStars()
    {
        for (int i = 0; i<lineCount; i++) {
            Vector<StarModel *> * lineArray;
            dataSource->pushBack(lineArray);
            for (int j = 0; j<rowCount; j++) {
                int type = arc4random()%typeCount;
                StarModel* model = new StarModel();
                model->type = type;
                model->line = i;
                model->row = j;
                lineArray->pushBack(model);
            }
        }
    }
    
    //判断上下左右
    void checkFourSides(StarModel* model)
    {
        if (checkedBlocks->contains(model)) {
            return;
        }else {
            checkedBlocks->pushBack(model);
        }
        checkUp(model);
        checkDown(model);
        checkLeft(model);
        checkRight(model);
    }
    
    void checkUp(StarModel* model) {
        StarModel* blockUpside = getModelForLineAndRow(model->line+1, model->row);
        if (blockUpside !=NULL || blockUpside->type != model->type) {
            return;
        }
        blocksInSameColor->pushBack(blockUpside);
        this->checkFourSides(blockUpside);
    }
    
    void checkDown(StarModel* model){
        StarModel* blockDownside = getModelForLineAndRow(model->line-1, model->row);
        if (blockDownside !=NULL || blockDownside->type != model->type) {
            return;
        }
        blocksInSameColor->pushBack(blockDownside);
        this->checkFourSides(blockDownside);
    }
    
    void checkLeft(StarModel* model){
        StarModel* blockLeftside = getModelForLineAndRow(model->line, model->row-1);
        if (blockLeftside !=NULL || blockLeftside->type != model->type) {
            return;
        }
        blocksInSameColor->pushBack(blockLeftside);
        this->checkFourSides(blockLeftside);
    }
    
    void checkRight(StarModel* model){
        StarModel* blockRightside = getModelForLineAndRow(model->line, model->row+1);
        if (blockRightside !=NULL || blockRightside->type != model->type) {
            return;
        }
        blocksInSameColor->pushBack(blockRightside);
        this->checkFourSides(blockRightside);
    }

    
};



#endif /* PopStarCore_h */
