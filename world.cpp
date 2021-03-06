#include "world.h"
#include "icon.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <queue>

void World::initWorld(string mapFile){
    ifstream ReadMap;
    ReadMap.open(mapFile.c_str());
    while(!ReadMap.eof()){
        string curline;
        getline(ReadMap,curline);
        int i = 0;string type = "";
        for(;curline[i]!=' ';i++){
            type += curline[i];
        }
        string x = "";
        for(i++;curline[i]!=' ';i++){
            x += curline[i];
        }
        int PosX = atoi(x.c_str());
        string y = "";
        for(i++;i<curline.length();i++){
            y += curline[i];
        }
        int PosY = atoi(y.c_str());
        if(type.compare("player")==0){
            this->_player.initObj(type);
            this->_player.setPosX(PosX);
            this->_player.setPosY(PosY);
        }
		else if (type.compare("cross") == 0) {
			Player e;
			e.initObj(type);
			e.setPosX(PosX);
			e.setPosY(PosY);
			this->_enemies.push_back(e);
		}
        else{
			RPGObj* p = new RPGObj(type, PosX, PosY);
            this->_objs.push_back(*p);
        }
        std::cout<<type<<' '<<PosX<<' '<<PosY<<std::endl;
    }
    //TODO 下面这部分逻辑应该是读入地图文件，生成地图上的对象
    //player 5 5
    /*
    this->_player.initObj("player");
    this->_player.setPosX(5);
    this->_player.setPosY(5);

    RPGObj obj1, obj2, obj3;
    obj1.initObj("stone");
    obj1.setPosX(4);
    obj1.setPosY(3);

    obj2.initObj("stone");
    obj2.setPosX(6);
    obj2.setPosY(5);

    obj3.initObj("fruit");
    obj3.setPosX(6);
    obj3.setPosY(8);

    this->_objs.push_back(obj1);
    this->_objs.push_back(obj2);
    this->_objs.push_back(obj3);
    */
}


void World::show(QPainter * painter){
	if (!_sync) return;
	_sync = false;
    RPGObj f;f.initObj("floor");
    for(int i = 0;i<=24;i++){
        for(int j = 0;j<=20;j++){
            f.show(painter,i,j);
        }
    }
	vector<RPGObj> allElem;
    for(auto it=this->_objs.begin();it!=this->_objs.end();++it){
        //(*it).show(painter);
		if (it->getErased())
			continue;
		allElem.push_back(*it);
    }
	allElem.push_back(_player);
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
		//(*it).show(painter);
		allElem.push_back(*it);
	sort(allElem.begin(), allElem.end());
	for (auto it = allElem.begin(); it != allElem.end(); ++it)
		(*it).show(painter);
	_sync = true;
}

void World::handlePlayerMove(int direction, int steps){
	int rtn;
    if((rtn = isCrashed(_player,direction,steps)) == 2) return;
	if (rtn == 3) exit(0);
    _player.move(direction, steps);
}
void World::handleEnemyMove(Player &e,int directions) {
	int rtn;
	if ((rtn = isCrashed(e,directions,1)) == 2) return;
	if (rtn == 3) exit(0);
	e.move(directions);
}
inline bool inRange(int a,int inf,int sup){
    if(a>=inf&&a<=sup) return true;
    else return false;
}
int World::isCrashed(Player p,int direction,int steps){
    int curX = p.getCPosX();
    int curY = p.getCPosY();
    switch (direction){
        case 1:
            curY -= steps;
            break;
        case 2:
            curY += steps;
            break;
        case 3:
            curX -= steps;
            break;
        case 4:
            curX += steps;
            break;
    }

	if (p.getObjType().compare("cross") == 0) {
		if (curX == _player.getCPosX() && curY == _player.getCPosY()) return 3;
	}

    for(vector<RPGObj>::iterator it = _objs.begin();it!=_objs.end();++it){
        if(inRange(curX,(*it).getCPosX(),(*it).getCPosX()+(*it).getCWidth() - 1)
			&& inRange(curY, (*it).getCPosY(), (*it).getCPosY() + (*it).getCHeight() - 1)) {
			if ((*it).canEat()) {
				(*it).erase();
				return 1;
			}
			else if (!(*it).canCover()) return 2;
			else if ((*it).isDeathly()) return 3;
		}
    }
	for (vector<Player>::iterator it = _enemies.begin(); it != _enemies.end(); ++it) {
		if (inRange(curX, (*it).getCPosX(), (*it).getCPosX() + (*it).getCWidth() - 1)
			&& inRange(curY, (*it).getCPosY(), (*it).getCPosY() + (*it).getCHeight() - 1)) {
			if (!(*it).getObjType().compare("player")) return 3;
		}
	}
    return 0;
}


void World::save(string mapFile){
    ofstream WriteMap;
    WriteMap.open(mapFile.c_str(),ios::ate);
    WriteMap<<"player "<<_player.getPosX()<<' '<<_player.getPosY();
    for(vector<RPGObj>::iterator it = _objs.begin();it!=_objs.end();++it){
		if (it->getErased()) continue;
        WriteMap<<std::endl<<(*it).getObjType()<<' '<<(*it).getPosX()<<' '
               <<(*it).getPosY();
    }
	for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
		WriteMap << std::endl << (*it).getObjType() << ' ' << (*it).getPosX() << ' '
			<< (*it).getPosY();
	}
}

void World::allEnemyMove()
{
	//_player.move(rand() % 4 + 1);
	for (auto I = _enemies.begin(); I != _enemies.end(); ++I)
	{
		handleEnemyMove((*I), rand() % 4 + 1);
	}
}