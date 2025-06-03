#include "JunqiBoard.h"
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QtCore/QDebug>//debug输出用
//#include <QBasicTimer>//定时器，闪烁效果
JunqiBoard::~JunqiBoard()
{

}

bool JunqiBoard::getRowCol(QPoint pt, int& row, int& col)
{

	//棋子的中心是 (hori * j * pWidth) - stoneWidth / 2 ;(i)*pLength - stoneHeight / 2, stoneWidth, stoneHeight。 反求i,j
	int xPos = pt.rx();//x坐标的引用，用引用因为后续可能对其修改。
	int yPos = pt.ry();
	col = (xPos + stoneWidth / 2) / hori / pWidth; //理论上整除就是i和j
	row = (yPos + stoneHeight / 2);//row是行
	row = row / pLength;
	int deltx = abs(xPos - (hori * col * pWidth - stoneWidth / 2));
	int delty = abs(yPos - (row * pLength - stoneHeight / 2));
	bool isInBoard;
	isInBoard = (deltx <= (stoneWidth)) && (delty <= (stoneHeight));
	//竖向不超过竖边长
	//横向不超过横边长
	//在棋框中则是true

	if (row < 1)
		isInBoard = false;
	else if (row <= 6)
	{
	}
	else if (row > 6 && row <= 12+ mountSize)
	{
		row = row - mountSize;
	}
	else
		isInBoard = false;
	//if (col < 1) isInBoard = false;
	//if (col > 5) isInBoard = false;

	

	
	//qDebug() << row << "," << col<<","<< isInBoard;
	return isInBoard;
}

void JunqiBoard::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen road = painter.pen();//公路的细线，对应默认笔刷
	QPen campLine(Qt::red, 2);//行营的轮廓
	QBrush campBrush(Qt::white, Qt::SolidPattern);//行营填充
	QPen stationLine(Qt::black, 2);//大本营轮廓
	QBrush stationBrush(Qt::white, Qt::SolidPattern);//大本营填充

	QPen rail(Qt::black, 3, Qt::DashLine);//铁路粗的黑白相间
	QVector<qreal> dashPattern = { 2, 2 }; // 每2个像素显示2个像素的实线，铁路
	
	rail.setDashPattern(dashPattern);
	for (int i = 1; i <= 6; ++i)//横着6条线
	{
		if (i == 2 || i == 6)
		{
			painter.setPen(rail);
		}
		else
		{
			painter.setPen(road);
		}
		painter.drawLine(QPoint(hori *pWidth, i*pLength), QPoint((hori*5)*pWidth, i*pLength));
	}
	//等一下山界
	for (int i = 7; i <= 12; ++i)
	{
		if (i == 7 || i == 11)
		{
			painter.setPen(rail);//横向铁路
		}
		else
		{
			painter.setPen(road);//其余公路
		}
		painter.drawLine(QPoint(hori *pWidth, (mountSize+i) * pLength), QPoint((hori*5) * pWidth, (mountSize+i) * pLength));
	}
	//竖线
	for (int i = 1; i <= 5; ++i)
	{
		if (i == 1 || i == 5)
		{
			//两侧铁路
			painter.setPen(rail);
			painter.drawLine(QPoint(hori * i * pWidth, 2*pLength), QPoint(hori * i * pWidth, (12+ mountSize-1) * pLength));
			painter.setPen(road);
			painter.drawLine(QPoint(hori * i * pWidth, 1 * pLength), QPoint(hori * i * pWidth, 2 * pLength));//上玩家 5行到底线的一条公路
			painter.drawLine(QPoint(hori * i * pWidth, (12 + mountSize - 1) * pLength), QPoint(hori * i * pWidth, (12 + mountSize ) * pLength));//下玩家 5行到底线的一条公路
		}
		else if (i == 3)
		{
			//中间铁路
			painter.setPen(road);
			painter.drawLine(QPoint(hori * 3 * pWidth, 1 * pLength), QPoint(hori * 3 * pWidth, 6 * pLength));
			painter.drawLine(QPoint(hori * 3 * pWidth, (7 + mountSize) * pLength), QPoint(hori * 3 * pWidth, (12 +mountSize) * pLength));
			painter.setPen(rail);
			painter.drawLine(QPoint(hori * 3 * pWidth, 6 * pLength), QPoint(hori * 3 * pWidth, (7+mountSize) * pLength));
		}
		else
		{
			//其余公路
			painter.setPen(road);
			painter.drawLine(QPoint(hori*i*pWidth, pLength), QPoint(i * pWidth, 6 * pLength));
			painter.drawLine(QPoint(hori*i*pWidth,(7+ mountSize)*pLength), QPoint(i * pWidth, (12 + mountSize) * pLength));
		}

	}
	//斜向公路线
	painter.setPen(road);
	for (int j = 0; j <= 1; j++)
	{
		painter.drawLine(QPoint(1 * hori * pWidth, (2+j*(5 + mountSize)) * pLength), QPoint(5 * hori * pWidth,  (6+j* (5 + mountSize)) * pLength));
		painter.drawLine(QPoint(1 * hori * pWidth, (6+j* (5 + mountSize)) * pLength), QPoint(5 * hori * pWidth, (2+j* (5 + mountSize)) * pLength));
		painter.drawLine(QPoint(3 * hori * pWidth, (2+j* (5 + mountSize)) * pLength), QPoint(5 * hori * pWidth, (4+j* (5 + mountSize)) * pLength));
		painter.drawLine(QPoint(1 * hori * pWidth, (4+j* (5 + mountSize)) * pLength), QPoint(3 * hori * pWidth, (6+j* (5 + mountSize)) * pLength));
		painter.drawLine(QPoint(3 * hori * pWidth, (2+j* (5 + mountSize)) * pLength), QPoint(1 * hori * pWidth, (4+j* (5 + mountSize)) * pLength));
		painter.drawLine(QPoint(5 * hori * pWidth, (4+j* (5 + mountSize)) * pLength), QPoint(3 * hori * pWidth, (6+j* (5 + mountSize)) * pLength));
	}
	//画兵站，行营，大本营
	for (int i = 1; i <= 12; i++)//12行
	{
		for (int j = 1; j <= 5; j++)//5列
		{
			if ((i == 3 && j == 2) || (i == 3 && j == 4) || (i == 4 && j == 3) || (i == 5 && j == 2) || (i == 5 && j == 4))
			{ 
				//本侧行营
				painter.setPen(campLine);
				painter.setBrush(campBrush);
				painter.drawEllipse(j * hori* pWidth - campRadius, i* pLength - campRadius, 2 * campRadius, 2 * campRadius);
			}
			else if ((i == 8 && j == 2) || (i == 8 && j == 4) || (i == 9 && j == 3) || (i == 10 && j == 2) || (i == 10 && j == 4))
			{
				//对侧行营
				painter.setPen(campLine);
				painter.setBrush(campBrush);
				painter.drawEllipse(j * hori * pWidth - campRadius, (i + mountSize) * pLength - campRadius, 2 * campRadius, 2 * campRadius);
			}
			else if ((i == 1 && j == 2)|| (i == 1 && j == 4))
			{
				//本侧大本营
				painter.setPen(stationLine);
				painter.setBrush(stationBrush);
				painter.drawRect((hori * j * pWidth) - headSize *stationWidth / 2, (i)*pLength - headSize *stationHeight / 2, headSize *stationWidth, headSize *stationHeight);
			}
			else if ((i == 12 && j == 2) || (i == 12 && j == 4))
			{
				//对侧大本营
				painter.setPen(stationLine);
				painter.setBrush(stationBrush);
				painter.drawRect((hori * j * pWidth) - headSize *stationWidth / 2, (i + mountSize)*pLength - headSize *stationHeight / 2, headSize *stationWidth, headSize *stationHeight);
			}
			else 
			{
				painter.setPen(QPen(Qt::black, 2));
				painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
				if (i >= 7)
				{
					//普通兵站对侧
					painter.drawRect((hori * j * pWidth) - stationWidth / 2, (i + mountSize) * pLength - stationHeight / 2, stationWidth, stationHeight);
				}
				else
				{
					//普通兵站本侧
					painter.drawRect((hori * j * pWidth) - stationWidth / 2, (i)*pLength - stationHeight / 2, stationWidth, stationHeight);
				}
			}
			
			
		}
	}

	//绘制棋子
	for (int i = 0; i < 50; i++)
	{
		drawStone(painter, i);
	}
	//drawStone(painter, i);

	
}


void JunqiBoard::drawStone(QPainter& painter, int id)
{
	if (Stones[id].isDead)
	{
		return;
	}
	//先初始化两个颜色笔刷
	QPen stonePenRed(Qt::black, 2);//红色边框
	QBrush stoneBrushRed(Qt::yellow, Qt::SolidPattern);//填充
	QPen stonePenBlue(Qt::black, 2);//蓝色边框
	QBrush stoneBrushBlue(Qt::cyan, Qt::SolidPattern);//填充
	QBrush stoneBrushGray(Qt::gray, Qt::SolidPattern);//被选中是灰色
	int j = Stones[id].y;//列
	int i = Stones[id].x;//行

	//int j = animatedY;//列
	//int i = animatedX;//行

	QRect rect;

	if (i < 7)//在上面，正常画
	{
		rect = QRect((hori * j * pWidth) - stoneWidth / 2, (i)*pLength - stoneHeight / 2, stoneWidth, stoneHeight);
	}
	else    //在这边，则要隔一个山界的距离
	{
		rect = QRect((hori * j * pWidth) - stoneWidth / 2, (i + mountSize) * pLength - stoneHeight / 2, stoneWidth, stoneHeight);
	}
	

	if (id < 25)//对面的棋子
	{
		
		painter.setPen(stonePenRed);
		painter.setBrush(stoneBrushRed);
		
		painter.drawRect(rect);
		//painter.drawText(rect, Stones[id].getText(), QTextOption(Qt::AlignCenter));
	}
	else
	{
		painter.setPen(stonePenBlue);
		
		if (id == selectId)
		{
			painter.setBrush(stoneBrushGray);;//选中半透明效果
		}
		else
		{
			painter.setBrush(stoneBrushBlue);
		}
		//无论是我方棋子还是对方棋子，区别的只有颜色。过山界后操作应是一样的
	
		painter.drawRect(rect);
		painter.setFont(QFont(QString::fromLocal8Bit("宋体"), 10, -1, false));
		//painter.setPen(Qt::white);
		painter.drawText(rect, Stones[id].getText(), QTextOption(Qt::AlignCenter));
		
	}
}


