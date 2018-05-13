#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>

using namespace std;

class RPGObj
{
public:
	RPGObj(){}
    RPGObj(string type, int posx, int posy): _pos_x(posx), _pos_y(posy), _erased(false)
    {
        initObj(type);
    }
    void initObj(string type);
    void show(QPainter * painter);
    void show(QPainter *painter,int x,int y);

    void setPosX(int x){_pos_x = x; }
    void setPosY(int y){_pos_y = y; }
	void erase() { _erased = true; }

    int getPosX() const{return _pos_x; }
    int getPosY() const{return _pos_y; }
    int getHeight() const{return _icon.getHeight(); }
    int getWidth() const{return _icon.getWidth(); }
    bool getErased() const {return _erased; }
    int getCPosX() const { return _pos_x + GAME_IMPACT_SET[getObjType()][2]; }
	int getCPosY() const { return _pos_y + GAME_IMPACT_SET[getObjType()][3]; }
    int getCHeight() const {return GAME_IMPACT_SET[getObjType()][1]; }
	int getCWidth() const { return GAME_IMPACT_SET[getObjType()][0]; }
    //virtual void interact(RPGObj &obj);
    string getObjType() const{return this->_icon.getTypeName();}//返回类名

	bool canCover() const { return _coverable; }
	bool canEat() const { return _eatable; }
	bool isDeathly() const { return _deathly; }
	bool operator < (const RPGObj& rhs) const { return getCPosY() < rhs.getCPosY(); }
protected:
    //所有坐标，单位均为游戏中的格
	bool _eatable;
	bool _coverable;
	bool _deathly;

    QImage _pic;
    int _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    bool _erased; //删除标记
    static map<string, int*> GAME_IMPACT_SET; //存放碰撞的长宽，第一维是x，第二维是y, 第三维是x方向偏移, 第四维是y方向偏移
};

#endif // RPGOBJ_H
