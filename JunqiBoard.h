#pragma once
#include <QtCore/QDebug>//debug输出用
#include <QWidget>
#include "Stone.h"
class JunqiBoard  : public QWidget
{
	Q_OBJECT

public:
	//QMap<int,QMap<int, Stone&>>map;//第x，y位置存入棋子的引用
	QMap<int, QMap<int, int>>map; //从1，1开始的动态空间，第m行第n列就对应m, n
	//int map[13][6];//或者外面留一圈空白有安全感，且第m行第n列就对应m,n
	//QMap<int, QMap<int, int>>distance;//存储距离的
	int selectId;//被点选的棋子的id
	bool pendingChange;//需要等待下一个操作，以交换
	int pWidth = 80, pLength = 40;//认为是长宽比例的基础单位
	int vert = 16, hori = 1.2;//垂直和水平方向，基础单位长宽的倍数
	int stationWidth = pWidth / 3, stationHeight = pLength / 3;//兵站宽度长度
	int stoneWidth = pWidth / 5*2, stoneHeight = pLength / 2;//棋子宽度长度
	int campRadius = 18;//行营圆圈的半径
	float headSize = 2;//大本营大小是兵站的多少倍
	int mountSize = 3;//山界长度
	Stone Stones[50];//棋子，前25为对方

	JunqiBoard(QWidget* parent = nullptr) : QWidget(parent)
	{
		//先给所有点位赋值99
		for (int i = 1; i <= 12; i++)
		{
			for (int j = 1; j <= 5; j++)
			{
				map[i][j] = 99;//99表示没有子
			}
		}
		//再按布局给兵站位置赋值
		for (int i = 0; i < 50; i++)
		{
			Stones[i].init(i);//初始化
			map[Stones[i].x][Stones[i].y] = Stones[i].value;
			selectId = -1;
		}
		//下面是debug用，检查位置是否正确。
		printBoard();

		
		
		//我这里还需要对map的初始化
	};
	
	bool getRowCol(QPoint pt, int& row, int& col);//用现在坐标求第几行第几列抽象坐标

	void printBoard()
	{
		for (int i = 1; i <= 12; i++)
		{
			for (int j = 1; j <= 5; j++)
			{
				qDebug() << i << "," << j << " is" << map[i][j] << " ";
			}
			qDebug() << "\n";
		}

	};

	void drawStone(QPainter& painter, int id);//绘制棋子
	void paintEvent(QPaintEvent*);//绘制棋盘
	//void mouseReleaseEvent(QMouseEvent*);//鼠标释放操作，一般认为释放后才有效，一直按着不行
	virtual ~JunqiBoard();
public:
	float animatedX; // 动画中的X位置
	float animatedY; // 动画中的Y位置

};