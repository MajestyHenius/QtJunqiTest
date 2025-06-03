#include "BoardTobattle.h"
#include <QMouseEvent>
#include <QtCore/QDebug>//debug输出用


bool BoardTobattle::isOnRail(int row, int col)//是否在铁轨上
{
	if (row == 1 || row == 12)
		return false;
	if (row == 2 || row == 6 || row == 7 || row == 11)
		return true;
	if (col == 1 || col == 5 || (col == 3 && (row == 6 || row == 7)))
		return true;
	return false;
}
//void BoardTobattle::saveRoute(int fromRow, int fromCol, int toRow, int toCol)
//{
	//route.resize(0);
	//for (QPoint at = QPoint( toRow, toCol); at != QPoint(-1, -1); at = parent[at.x()][at.y()]) //得好好理解理解
	//{
	//	path.push_back(at);
	//}
	//std::reverse(path.begin(), path.end());
	//qDebug() << "Route: ";
	//for (const auto& p : path) 
	//{
	//	qDebug() << "(" << p.x() << ", " << p.y() << ") ";
	//}
	//qDebug() << "\n";
	//假设在这里已经用完了行走完了，就要消除掉。
	//path.~QVector();
//}

int BoardTobattle::BFS_Engineer(int fromRow,int fromCol,int toRow,int toCol) //工兵的BFS算法
{
	//建立一个队列
	QQueue<QPoint> queue;
	//int g[11][5];//图表示铁路连通性，和map不太一样，不是很好沿用。
	//int dist[11][5];//距离
	//int parent[11][5];//用于记录前驱。
	route.resize(0);
	memset(g, 1, sizeof g);
	memset(dist, -1, sizeof(dist));//距离先置零
	//待定
	/*for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			parent[i][j] = QPoint(-1, -1);
		}
	}*/

	//根据map初始化一下g
	
	for (int j = 0; j < 5; j++)//按列开始数
	{
		for (int i = 0; i < 5; i++)//上半边
		{
			if (map[i+2][j + 1] == 99)//空
				g[i][j] = 0;//无障碍
			else 
				g[i][j] = 1;//非空，
			
		}
		for (int i = 6; i < 11; i++)//下半边
		{
			if (map[i + 1][j + 1] == 99)//空
				g[i][j] = 0;//无障碍
			else
				g[i][j] = 1;//非空，
			
		}
		//但是还得排除行营公路部分3*3的两块

	}
	//排除两侧行营公路：
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			g[i][j] = 1;
		}
	}
	for (int i = 7; i < 10; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			g[i][j] = 1;
		}
	}
	g[5][0] = 0;
	g[5][2] = 0;
	g[5][4] = 0;
	g[5][1] = 1;//假设从map[6][2]到Map[7][2]有障碍物，中间公路区域也是不能走的
	g[5][3] = 1;

    //map的坐标有不同，先转化一下.
	int gx, gy;
	if (fromRow < 7)
		gx = fromRow - 2;
	else
		gx = fromRow - 1;
	gy = fromCol - 1;
	int tox, toy;
	if (toRow < 7)
		tox = toRow - 2;
	else
		tox = toRow - 1;
	toy = toCol - 1;

	//目标有子也要硬上：
	g[tox][toy] = 0;

	dist[gx][gy]=0;//起始点表示搜过了
	queue.enqueue(QPoint(gx, gy));//把点存入
	int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
	//上、右、下、左

	qDebug() << "start:(" << gx << "," << gy << ")to("<<tox<<","<<toy<<")\n";
	while (!queue.empty())
	{
		auto t = queue.head();
		queue.dequeue();//取出;
		qDebug() << "routing:(" << t.x() << "," << t.y() << ")\n";
		route.push_back(t);
		for (int i = 0; i < 4; i++)//四个方向
		{
			int x = t.x() + dx[i], y = t.y() + dy[i];//上下左右方向移动后的坐标
			if (x >= 0 && x < 11 && y >= 0 && y < 5 //没出界
				&& g[x][y] == 0 && dist[x][y] == -1)//且移动后的地方是空的且没被搜索过
			{
				dist[x][y] = dist[t.x()][t.y()] + 1;//这个地方被搜索过了。
				parent[x][y] = t;
				queue.enqueue(QPoint(x, y));//加入队列

				//到达终点立即返回
				if (x == tox && y == toy)
				{
					qDebug() << "received" << tox << "," << y << "\n";
					return dist[x][y];
					//else return false;
				}
			}
		}
	}

	return dist[tox][toy];

}//给工兵的BFS算法

bool BoardTobattle::clearRowPath(int Row,int fromCol, int toCol)//横是否无遮挡畅通。
{
	int iStart = qMin(fromCol, toCol);
	int iEnd = qMax(fromCol, toCol);
	for (int i = iStart + 1; i < iEnd; i++)
	{
		//找中间有没有子，如果有子，就不能在铁路移动
		//99表示这个位置没有子。
		if (map[Row][i] != 99)//这之间有不为空的子
		{
			return false;//认为不能移动
		}


	}
	return true;//竖向铁路相连，且中间没有阻挡，可以移动
}
bool BoardTobattle::clearColPath(int Col, int fromRow, int toRow)//纵是否无遮挡畅通。
{

	int iStart = qMin(fromRow, toRow);
	int iEnd = qMax(fromRow, toRow);
	for (int i = iStart + 1; i < iEnd; i++)
	{
		//找中间有没有子，如果有子，就不能在铁路移动
		//99表示这个位置没有子。
		if (map[i][Col] != 99)
		{
			return false;
		}

	}
	return true;//竖向铁路相连，且中间没有阻挡，可以移动


	
}



bool BoardTobattle::canMove(int fromRow, int fromCol,int toRow, int toCol)//判断能否走棋，输入不应该是两个棋子id。
{

	//int fromRow = Stones[fromId].x;
	//int fromCol = Stones[fromId].y;
	//int toRow = Stones[toId].x;
	//int toCol = Stones[toId].y;
	qDebug() << "from" << fromRow << "," << fromCol << "to" << toRow << "," << toCol << "\n";
	int fromValue = map[fromRow][fromCol];
	int toValue = map[toRow][toCol];
	//虽然地雷和军旗已经在外面选择时候排除了，保险在这里再写一层。
	if (fromRow == 1&&fromCol == 2 || fromRow == 1 && fromCol == 4 || fromRow == 12 && fromCol == 2 || fromRow == 12 && fromCol == 4)//排除大本营里的子
		return false;
	if (fromValue == 41 || fromValue == -1)//排除自身是军旗和雷
		return false;


	bool isInRowRail;//横向是铁路连接的
	bool isInColRail;
	
	//下面是列举了各种可能的情况，有没有能自动一点的算法？
	//但是O(999)也是O(1)，先写了吧
	isInRowRail = (fromRow == toRow) && (fromRow == 2 || fromRow == 6 || fromRow == 7 || fromRow == 11);//是同一横线铁路上的
	bool haveButtomWay = fromRow == 1 || fromRow == 12 || toRow == 1 || toRow == 12;//来的方向或者去的地方有一个是底线
	bool isIn67 = (fromRow == 6 && toRow == 7) || (fromRow == 7 && toRow == 6);
	isInColRail = (!haveButtomWay)&&(fromCol == toCol) && (fromCol==1 || fromCol == 5 || (fromCol == 3 && isIn67));//是同一竖线的铁路上的
	//            都不是底线子      在同一列            第一列或者第五列            或者第三列的六七行


	if (fromValue == 32 && isOnRail(fromRow, fromCol) && isOnRail(toRow, toCol))//是工兵，起点和终点都在铁路上
	{
		if (BFS_Engineer(fromRow, fromCol, toRow, toCol) != -1)
		{
			//saveRoute(fromRow,fromCol, toRow, toCol);
			return true;
		}
		else
			return false;
		
		
	}
	//其余：
	if (isInRowRail)//是横线铁路上的，判断横线之间有没有间隔，不适用于工兵，因为工兵可能绕路
	{
		return clearRowPath(fromRow, fromCol, toCol);
	}
	if (isInColRail)//是竖线铁路上的，判断竖线之间有没有间隔不适用于工兵，因为工兵可能绕路
	{
		return clearColPath(fromCol, fromRow, toRow);
	}

	

	//判断完铁路条件，判断其他情况
	//计算距离
	int dist = abs(fromRow - toRow) + abs(fromCol - toCol);
	
	if (dist == 1)//只有一格距离，是可以移动的
	{
		if (fromCol == toCol && (fromCol == 2 || fromCol == 4)&&((fromRow==6&& toRow==7)|| (fromRow == 7 && toRow == 6)))
			return false;
		return true;
	}
	if (dist > 2)//远超对角线的情况，而且不是工兵，直接判定不能移动。
	{
		return false;
	}
	else if (dist == 2 )//斜对角的情况
	{
		if (fromRow == toRow || fromCol == toCol)//两者距离为2且在同一行/列
			return false;
		if (haveButtomWay)//是底线的子
			return false;

		if (fromRow < 7 && toRow < 7) //都在上面侧
		{
			int fromTotal = fromRow + fromCol;
			int toTotal = toRow + toCol;
			if ((fromTotal % 2 == 1) && toTotal % 2 == 1)//两个总和都是奇数，说明在合适的对角可以移动。
			{
				if (!(toRow == 2 || toRow == 4 || toRow == 6))//是行营位置
				{
					if (map[toRow][toCol] == 99)//是空的
					{
						return true;
					}
					else
						return false;

				}
				else //不是行营位置，其他位置，都可以去。
					return true;

			}
		}
		else if (fromRow >= 7 && toRow >= 7)//都在下侧
		{
			int fromTotal = 13 - fromRow + fromCol;
			int toTotal = 13 - toRow + toCol;
			if ((fromTotal % 2 == 1) && toTotal % 2 == 1)//两个总和都是奇数，说明在合适的对角可以移动。
			{
				if (!(toRow == 7 || toRow == 9 || toRow == 11))//是行营位置
				{
					if (map[toRow][toCol] == 99)//是空的
					{
						return true;
					}
					else
						return false;

				}
				else //不是行营位置，其他位置，都可以去。
					return true;
			}
		}
	}
	//最后是工兵的情况。
	
	
	return false;
		
	
}


void BoardTobattle::moveAnimation(int fromRow, int fromCol, int toRow, int toCol)//给其他子形式移动播放动画
{
	if (Stones[selectId].isDead)
		return;

	//animatedX = fromRow;
	//animatedY = fromCol;
	Stones[selectId].x = fromRow;
	Stones[selectId].y = fromCol;
	
	endx = toRow;
	endy = toCol;
	animationStep = 0; // 重置动画步骤

	animationTimer->start(50); // 每50毫秒更新一次



}




void BoardTobattle::updateAnimation() //动画
{
	if (animationStep < 20) 
	{ // 进行20步动画
		float rowInterval = (endx - startx)  / 20.0f; // 行增量
		float colInterval = (endy- starty)  / 20.0f; // 列增量

		// 更新棋子位置
		animatedX = startx + static_cast<int>(animationStep * rowInterval);
		animatedY = starty + static_cast<int>(animationStep * colInterval);

		animationStep++; // 增加动画步骤
		update(); // 请求重绘
	}
	else 
	{
		Stones[selectId].x = endx;
		Stones[selectId].y = endy;
		animationTimer->stop(); // 停止定时器
	}
}




void BoardTobattle::mouseReleaseEvent(QMouseEvent* event)//适合处理事件不同，放到子类中
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
		if (Stones[i].x == row && Stones[i].y == col && (!Stones[i].isDead))
		{
			qDebug() << row << "," << col << QString::fromLocal8Bit("被选中");
			break;

		}
	}

	if (i < 50)//能点的子。这里应该不小于25
	{
		clickId = i;//点过的棋子
		
	}


	if (selectId == -1)//之前没点过别的子
	{
		qDebug() << QString::fromLocal8Bit("点到第一个棋子");
		if (clickId != -1 && clickId >= 25)
			//&& clickId >= 25)//点过棋子而且不是敌人的子,暂时恢复，用于测试敌人行营
			//此外,在测试操纵敌人子移动时候,map也要相应更新.
		{
			startx = Stones[selectId].x;
			starty = Stones[selectId].y;


			selectId = clickId;
			update();
		}
	}
	else//下次点击
	{
		qDebug() << QString::fromLocal8Bit("点到第二个棋子");
		
		if (Stones[selectId].value == 41|| Stones[selectId].value == -1)//我本身是个地雷，再去哪里都不行，回去。
		{
			qDebug() << QString::fromLocal8Bit("地雷/军旗不能移动");
			selectId = -1;
			update();
			return;
		}
		if (clickId >= 25)//点的是还自己的子，换新点的子
		{
			selectId = clickId;
			update();
			return;
		}

		if (clickId == -1)//说明是点的棋盘其他位置，看看从原始位置到这个位置能不能走
		{
			if (!canMove(Stones[selectId].x, Stones[selectId].y, row, col))//要去的位置不符合移动要求,回去重新点
			{
				selectId = -1;
				update();
				return;
			}
			else//要去的位置符合要求
			{
				map[Stones[selectId].x][Stones[selectId].y] = 99;//原来位置置空
				//qDebug() << "from" << fromRow << "," << fromCol << "to" << toRow << "," << toCol << "\n";
				
				
				//endx = row; 
				//endy = col;
				//moveAnimation(startx,starty,endx,endy);//移动动画
				Stones[selectId].x = row;
				Stones[selectId].y = col;//选的子移动过去
				map[row][col] = Stones[selectId].value;//并且在map中记录
				//printBoard();
			}
		}
		else//点的是敌人的子,要发起进攻
		{
			if (!canMove(Stones[selectId].x, Stones[selectId].y, row, col))//要去的位置不符合移动要求,回去重新点
			{
				selectId = -1;
				update();
				return;
			}
			else 
			{
				//在这之前判断能不能吃过
				//eatResult,0,-1，1
				//0,两个都消失。1,过去吃掉，-1，过去死掉
				map[Stones[selectId].x][Stones[selectId].y] = 99;//原来位置置空
				Stones[selectId].x = row;
				Stones[selectId].y = col;//选的子移动过去
				Stones[clickId].isDead = true;//被点到的子暂时消失
				map[row][col] = Stones[selectId].value;//并且在map中记录
			}
			

		}


		
		
		


		//如果点隔着路，没有直接相连的点，也返回
		//也许可以写一个输入A，B点，返回能不能直达。

		//子先过去
		
		//加移动的过渡动画
		//加一个canMove
		selectId = -1;
		update();
	}

}




BoardTobattle::~BoardTobattle()
{}