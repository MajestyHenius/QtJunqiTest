#include "BoardEmbattle.h"
#include <QMouseEvent>
#include <QtCore/QDebug>//debug输出用
//只管布局，继承自棋盘类


BoardEmbattle::~BoardEmbattle()
{}


void BoardEmbattle::mouseReleaseEvent(QMouseEvent* event)//适合处理事件不同，放到子类中
{
	QPoint pt = event->pos();//位置
	int row, col;
	bool bRet = getRowCol(pt, row, col);
	if (!bRet)
		return;//没选中，无事发生

	int i;
	int clickId = -1;
	//首先不是行营和奇怪的点
	for (i = 0; i < 50; i++)
	{
		if (Stones[i].x == row && Stones[i].y == col)
		{
			//说明这个棋子被选中了
			if (row > 6)
			{
				qDebug() << row << "," << col << QString::fromLocal8Bit("被选中");
				break;
			}
		}
	}
	if (i >= 25 && i < 50)//先做下边玩家的
	{
		//if(row!=)//并且选择的得是棋子啊
		clickId = i;
	}

	if (selectId == -1)//第一次点击
	{
		qDebug() << QString::fromLocal8Bit("点到第一个棋子");
		if (clickId != -1)//点到一个棋子
		{
			selectId = clickId;
			update();
		}
	}
	else//下次点击
	{
		qDebug() << QString::fromLocal8Bit("点到第二个棋子");
		if (clickId != -1)//又点到一个棋子
		{
			//炸弹不能在第一排:
			if ((Stones[selectId].value == 0 && row < 8) || (Stones[clickId].value == 0 && Stones[selectId].x < 8))
			{
				//selectId = -1;
				qDebug() << QString::fromLocal8Bit("炸弹不能放第一排");
			}
			//地雷不能在1 - 4排，军棋不能出大本营
			else if ((Stones[selectId].value == 41 && row < 11) || (Stones[clickId].value == 41 && Stones[selectId].x < 11))
			{
				qDebug() << QString::fromLocal8Bit("炸弹不能放第5排以前");
			}
			else if ((Stones[selectId].value == -1 && row != 6 && (col != 2 && col != 4)) ||
				(Stones[clickId].value == -1 && Stones[selectId].x != 6 && (Stones[selectId].y != 2 && Stones[selectId].y != 4)))
			{
				qDebug() << QString::fromLocal8Bit("军旗不能放在大本营外");
			}
			else
			{
				Stones[clickId].x = Stones[selectId].x;
				Stones[clickId].y = Stones[selectId].y;//别的棋子交换
				Stones[selectId].x = row;
				Stones[selectId].y = col;

			}
			selectId = -1;
			update();
		}
	}

}