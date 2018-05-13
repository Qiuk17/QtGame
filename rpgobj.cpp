#include "rpgobj.h"
#include <iostream>
#include <icon.h>

pair<string, int*> _pairArray[] =
{
	make_pair("player", new int[4]{1, 1, 0, 1}),
	make_pair("stone", new int[4]{1, 1, 0, 0}),
	make_pair("fruit", new int[4]{1, 1, 0, 0}),
	make_pair("well", new int[4]{2, 2, 0, 0}),
	make_pair("pillar", new int[4]{1, 1, 0, 1}),
	make_pair("statue", new int[4]{1, 1, 0, 1}),
	make_pair("floor", new int[4]{0, 0, 0, 0}),
	make_pair("cross", new int[4]{1, 1, 0, 0})
};

map<string, int*> RPGObj::GAME_IMPACT_SET(_pairArray, _pairArray + sizeof(_pairArray) / sizeof(_pairArray[0]));

void RPGObj::initObj(string type)
{
    //TODO 所支持的对象类型应定义为枚举
	if (type.compare("player") == 0) {
		this->_coverable = false;
		this->_eatable = false;
		this->_deathly = true;
	}
	else if (type.compare("stone") == 0) {
		this->_coverable = false;
		this->_eatable = false;
		this->_deathly = false;
	}
	else if (type.compare("fruit") == 0) {
		this->_coverable = false;
		this->_eatable = true;
		this->_deathly = false;
	}
	else if (type.compare("well") == 0) {
		this->_coverable = false;
		this->_eatable = false;
		this->_deathly = false;
	}
	else if (type.compare("pillar") == 0) {
		this->_coverable = false;
		this->_eatable = false;
		this->_deathly = false;
	}
	else if (type.compare("statue") == 0) {
		this->_coverable = false;
		this->_eatable = false;
		this->_deathly = false;
	}
	else if (type.compare("floor") == 0) {
		this->_coverable = true;
		this->_eatable = false;
		this->_deathly = false;
	}
	else if (type.compare("cross") == 0) {
		this->_coverable = true;
		this->_eatable = false;
		this->_deathly = true;
	}
    else{
        //TODO 应由专门的错误日志文件记录
        cout<<"invalid ICON type."<<endl;
        return;
    }

    this->_icon = ICON::findICON(type);
    QImage all;
    all.load("C:\\Users\\apple\\Desktop\\QTgame\\TileB.png");
    this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
}

void RPGObj::show(QPainter * pa){
	int gSize = ICON::GRID_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}

void RPGObj::show(QPainter *pa, int x, int y){
    int gSize = ICON::GRID_SIZE;
    pa->drawImage(x*gSize,y*gSize,this->_pic);
}


