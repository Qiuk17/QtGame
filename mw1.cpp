#include "mw1.h"
#include "ui_mw1.h"
#include "icon.h"

#include <map>
#include <iostream>

using namespace std;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
	timer = new QTimer(this);
	QObject::connect(timer, &QTimer::timeout, this, &MW1::allEnemyMove);
    //init game world
    _game.initWorld("C:\\Users\\apple\\Desktop\\QTgame\\map.txt");//TODO 应该是输入有效的地图文件
	timer->start(10);
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *e){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}

void MW1::keyPressEvent(QKeyEvent *e)
{
    //direction = 1,2,3,4 for 上下左右
    if(e->key() == Qt::Key_A)
    {
        this->_game.handlePlayerMove(3,1);
    }
    else if(e->key() == Qt::Key_D)
    {
        this->_game.handlePlayerMove(4,1);
    }
    else if(e->key() == Qt::Key_W)
    {
        this->_game.handlePlayerMove(1,1);
    }
    else if(e->key() == Qt::Key_S)
    {
         this->_game.handlePlayerMove(2,1);
    }
    else if(e->key() == Qt::Key_P)
    {
        this->_game.save("C:\\Users\\apple\\Desktop\\QTgame\\map.txt");
    }
    this->repaint();
}

void MW1::allEnemyMove()
{
	_game.allEnemyMove();
	this->repaint();
}