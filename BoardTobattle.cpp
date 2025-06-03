#include "BoardTobattle.h"
#include <QMouseEvent>
#include <QtCore/QDebug>//debug�����


bool BoardTobattle::isOnRail(int row, int col)//�Ƿ���������
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
	//for (QPoint at = QPoint( toRow, toCol); at != QPoint(-1, -1); at = parent[at.x()][at.y()]) //�úú�������
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
	//�����������Ѿ��������������ˣ���Ҫ��������
	//path.~QVector();
//}

int BoardTobattle::BFS_Engineer(int fromRow,int fromCol,int toRow,int toCol) //������BFS�㷨
{
	//����һ������
	QQueue<QPoint> queue;
	//int g[11][5];//ͼ��ʾ��·��ͨ�ԣ���map��̫һ�������Ǻܺ����á�
	//int dist[11][5];//����
	//int parent[11][5];//���ڼ�¼ǰ����
	route.resize(0);
	memset(g, 1, sizeof g);
	memset(dist, -1, sizeof(dist));//����������
	//����
	/*for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			parent[i][j] = QPoint(-1, -1);
		}
	}*/

	//����map��ʼ��һ��g
	
	for (int j = 0; j < 5; j++)//���п�ʼ��
	{
		for (int i = 0; i < 5; i++)//�ϰ��
		{
			if (map[i+2][j + 1] == 99)//��
				g[i][j] = 0;//���ϰ�
			else 
				g[i][j] = 1;//�ǿգ�
			
		}
		for (int i = 6; i < 11; i++)//�°��
		{
			if (map[i + 1][j + 1] == 99)//��
				g[i][j] = 0;//���ϰ�
			else
				g[i][j] = 1;//�ǿգ�
			
		}
		//���ǻ����ų���Ӫ��·����3*3������

	}
	//�ų�������Ӫ��·��
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
	g[5][1] = 1;//�����map[6][2]��Map[7][2]���ϰ���м乫·����Ҳ�ǲ����ߵ�
	g[5][3] = 1;

    //map�������в�ͬ����ת��һ��.
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

	//Ŀ������ҲҪӲ�ϣ�
	g[tox][toy] = 0;

	dist[gx][gy]=0;//��ʼ���ʾ�ѹ���
	queue.enqueue(QPoint(gx, gy));//�ѵ����
	int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
	//�ϡ��ҡ��¡���

	qDebug() << "start:(" << gx << "," << gy << ")to("<<tox<<","<<toy<<")\n";
	while (!queue.empty())
	{
		auto t = queue.head();
		queue.dequeue();//ȡ��;
		qDebug() << "routing:(" << t.x() << "," << t.y() << ")\n";
		route.push_back(t);
		for (int i = 0; i < 4; i++)//�ĸ�����
		{
			int x = t.x() + dx[i], y = t.y() + dy[i];//�������ҷ����ƶ��������
			if (x >= 0 && x < 11 && y >= 0 && y < 5 //û����
				&& g[x][y] == 0 && dist[x][y] == -1)//���ƶ���ĵط��ǿյ���û��������
			{
				dist[x][y] = dist[t.x()][t.y()] + 1;//����ط����������ˡ�
				parent[x][y] = t;
				queue.enqueue(QPoint(x, y));//�������

				//�����յ���������
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

}//��������BFS�㷨

bool BoardTobattle::clearRowPath(int Row,int fromCol, int toCol)//���Ƿ����ڵ���ͨ��
{
	int iStart = qMin(fromCol, toCol);
	int iEnd = qMax(fromCol, toCol);
	for (int i = iStart + 1; i < iEnd; i++)
	{
		//���м���û���ӣ�������ӣ��Ͳ�������·�ƶ�
		//99��ʾ���λ��û���ӡ�
		if (map[Row][i] != 99)//��֮���в�Ϊ�յ���
		{
			return false;//��Ϊ�����ƶ�
		}


	}
	return true;//������·���������м�û���赲�������ƶ�
}
bool BoardTobattle::clearColPath(int Col, int fromRow, int toRow)//���Ƿ����ڵ���ͨ��
{

	int iStart = qMin(fromRow, toRow);
	int iEnd = qMax(fromRow, toRow);
	for (int i = iStart + 1; i < iEnd; i++)
	{
		//���м���û���ӣ�������ӣ��Ͳ�������·�ƶ�
		//99��ʾ���λ��û���ӡ�
		if (map[i][Col] != 99)
		{
			return false;
		}

	}
	return true;//������·���������м�û���赲�������ƶ�


	
}



bool BoardTobattle::canMove(int fromRow, int fromCol,int toRow, int toCol)//�ж��ܷ����壬���벻Ӧ������������id��
{

	//int fromRow = Stones[fromId].x;
	//int fromCol = Stones[fromId].y;
	//int toRow = Stones[toId].x;
	//int toCol = Stones[toId].y;
	qDebug() << "from" << fromRow << "," << fromCol << "to" << toRow << "," << toCol << "\n";
	int fromValue = map[fromRow][fromCol];
	int toValue = map[toRow][toCol];
	//��Ȼ���׺;����Ѿ�������ѡ��ʱ���ų��ˣ�������������дһ�㡣
	if (fromRow == 1&&fromCol == 2 || fromRow == 1 && fromCol == 4 || fromRow == 12 && fromCol == 2 || fromRow == 12 && fromCol == 4)//�ų���Ӫ�����
		return false;
	if (fromValue == 41 || fromValue == -1)//�ų������Ǿ������
		return false;


	bool isInRowRail;//��������·���ӵ�
	bool isInColRail;
	
	//�������о��˸��ֿ��ܵ��������û�����Զ�һ����㷨��
	//����O(999)Ҳ��O(1)����д�˰�
	isInRowRail = (fromRow == toRow) && (fromRow == 2 || fromRow == 6 || fromRow == 7 || fromRow == 11);//��ͬһ������·�ϵ�
	bool haveButtomWay = fromRow == 1 || fromRow == 12 || toRow == 1 || toRow == 12;//���ķ������ȥ�ĵط���һ���ǵ���
	bool isIn67 = (fromRow == 6 && toRow == 7) || (fromRow == 7 && toRow == 6);
	isInColRail = (!haveButtomWay)&&(fromCol == toCol) && (fromCol==1 || fromCol == 5 || (fromCol == 3 && isIn67));//��ͬһ���ߵ���·�ϵ�
	//            �����ǵ�����      ��ͬһ��            ��һ�л��ߵ�����            ���ߵ����е�������


	if (fromValue == 32 && isOnRail(fromRow, fromCol) && isOnRail(toRow, toCol))//�ǹ����������յ㶼����·��
	{
		if (BFS_Engineer(fromRow, fromCol, toRow, toCol) != -1)
		{
			//saveRoute(fromRow,fromCol, toRow, toCol);
			return true;
		}
		else
			return false;
		
		
	}
	//���ࣺ
	if (isInRowRail)//�Ǻ�����·�ϵģ��жϺ���֮����û�м�����������ڹ�������Ϊ����������·
	{
		return clearRowPath(fromRow, fromCol, toCol);
	}
	if (isInColRail)//��������·�ϵģ��ж�����֮����û�м���������ڹ�������Ϊ����������·
	{
		return clearColPath(fromCol, fromRow, toRow);
	}

	

	//�ж�����·�������ж��������
	//�������
	int dist = abs(fromRow - toRow) + abs(fromCol - toCol);
	
	if (dist == 1)//ֻ��һ����룬�ǿ����ƶ���
	{
		if (fromCol == toCol && (fromCol == 2 || fromCol == 4)&&((fromRow==6&& toRow==7)|| (fromRow == 7 && toRow == 6)))
			return false;
		return true;
	}
	if (dist > 2)//Զ���Խ��ߵ���������Ҳ��ǹ�����ֱ���ж������ƶ���
	{
		return false;
	}
	else if (dist == 2 )//б�Խǵ����
	{
		if (fromRow == toRow || fromCol == toCol)//���߾���Ϊ2����ͬһ��/��
			return false;
		if (haveButtomWay)//�ǵ��ߵ���
			return false;

		if (fromRow < 7 && toRow < 7) //���������
		{
			int fromTotal = fromRow + fromCol;
			int toTotal = toRow + toCol;
			if ((fromTotal % 2 == 1) && toTotal % 2 == 1)//�����ܺͶ���������˵���ں��ʵĶԽǿ����ƶ���
			{
				if (!(toRow == 2 || toRow == 4 || toRow == 6))//����Ӫλ��
				{
					if (map[toRow][toCol] == 99)//�ǿյ�
					{
						return true;
					}
					else
						return false;

				}
				else //������Ӫλ�ã�����λ�ã�������ȥ��
					return true;

			}
		}
		else if (fromRow >= 7 && toRow >= 7)//�����²�
		{
			int fromTotal = 13 - fromRow + fromCol;
			int toTotal = 13 - toRow + toCol;
			if ((fromTotal % 2 == 1) && toTotal % 2 == 1)//�����ܺͶ���������˵���ں��ʵĶԽǿ����ƶ���
			{
				if (!(toRow == 7 || toRow == 9 || toRow == 11))//����Ӫλ��
				{
					if (map[toRow][toCol] == 99)//�ǿյ�
					{
						return true;
					}
					else
						return false;

				}
				else //������Ӫλ�ã�����λ�ã�������ȥ��
					return true;
			}
		}
	}
	//����ǹ����������
	
	
	return false;
		
	
}


void BoardTobattle::moveAnimation(int fromRow, int fromCol, int toRow, int toCol)//����������ʽ�ƶ����Ŷ���
{
	if (Stones[selectId].isDead)
		return;

	//animatedX = fromRow;
	//animatedY = fromCol;
	Stones[selectId].x = fromRow;
	Stones[selectId].y = fromCol;
	
	endx = toRow;
	endy = toCol;
	animationStep = 0; // ���ö�������

	animationTimer->start(50); // ÿ50�������һ��



}




void BoardTobattle::updateAnimation() //����
{
	if (animationStep < 20) 
	{ // ����20������
		float rowInterval = (endx - startx)  / 20.0f; // ������
		float colInterval = (endy- starty)  / 20.0f; // ������

		// ��������λ��
		animatedX = startx + static_cast<int>(animationStep * rowInterval);
		animatedY = starty + static_cast<int>(animationStep * colInterval);

		animationStep++; // ���Ӷ�������
		update(); // �����ػ�
	}
	else 
	{
		Stones[selectId].x = endx;
		Stones[selectId].y = endy;
		animationTimer->stop(); // ֹͣ��ʱ��
	}
}




void BoardTobattle::mouseReleaseEvent(QMouseEvent* event)//�ʺϴ����¼���ͬ���ŵ�������
{
	QPoint pt = event->pos();//λ��
	int row, col;
	bool bRet = getRowCol(pt, row, col);
	if (!bRet)
		return;//ûѡ�У����·���

	int i;
	int clickId = -1;
	//���Ȳ�����Ӫ����ֵĵ�
	for (i = 0; i < 50; i++)
	{
		if (Stones[i].x == row && Stones[i].y == col && (!Stones[i].isDead))
		{
			qDebug() << row << "," << col << QString::fromLocal8Bit("��ѡ��");
			break;

		}
	}

	if (i < 50)//�ܵ���ӡ�����Ӧ�ò�С��25
	{
		clickId = i;//���������
		
	}


	if (selectId == -1)//֮ǰû��������
	{
		qDebug() << QString::fromLocal8Bit("�㵽��һ������");
		if (clickId != -1 && clickId >= 25)
			//&& clickId >= 25)//������Ӷ��Ҳ��ǵ��˵���,��ʱ�ָ������ڲ��Ե�����Ӫ
			//����,�ڲ��Բ��ݵ������ƶ�ʱ��,mapҲҪ��Ӧ����.
		{
			startx = Stones[selectId].x;
			starty = Stones[selectId].y;


			selectId = clickId;
			update();
		}
	}
	else//�´ε��
	{
		qDebug() << QString::fromLocal8Bit("�㵽�ڶ�������");
		
		if (Stones[selectId].value == 41|| Stones[selectId].value == -1)//�ұ����Ǹ����ף���ȥ���ﶼ���У���ȥ��
		{
			qDebug() << QString::fromLocal8Bit("����/���첻���ƶ�");
			selectId = -1;
			update();
			return;
		}
		if (clickId >= 25)//����ǻ��Լ����ӣ����µ����
		{
			selectId = clickId;
			update();
			return;
		}

		if (clickId == -1)//˵���ǵ����������λ�ã�������ԭʼλ�õ����λ���ܲ�����
		{
			if (!canMove(Stones[selectId].x, Stones[selectId].y, row, col))//Ҫȥ��λ�ò������ƶ�Ҫ��,��ȥ���µ�
			{
				selectId = -1;
				update();
				return;
			}
			else//Ҫȥ��λ�÷���Ҫ��
			{
				map[Stones[selectId].x][Stones[selectId].y] = 99;//ԭ��λ���ÿ�
				//qDebug() << "from" << fromRow << "," << fromCol << "to" << toRow << "," << toCol << "\n";
				
				
				//endx = row; 
				//endy = col;
				//moveAnimation(startx,starty,endx,endy);//�ƶ�����
				Stones[selectId].x = row;
				Stones[selectId].y = col;//ѡ�����ƶ���ȥ
				map[row][col] = Stones[selectId].value;//������map�м�¼
				//printBoard();
			}
		}
		else//����ǵ��˵���,Ҫ�������
		{
			if (!canMove(Stones[selectId].x, Stones[selectId].y, row, col))//Ҫȥ��λ�ò������ƶ�Ҫ��,��ȥ���µ�
			{
				selectId = -1;
				update();
				return;
			}
			else 
			{
				//����֮ǰ�ж��ܲ��ܳԹ�
				//eatResult,0,-1��1
				//0,��������ʧ��1,��ȥ�Ե���-1����ȥ����
				map[Stones[selectId].x][Stones[selectId].y] = 99;//ԭ��λ���ÿ�
				Stones[selectId].x = row;
				Stones[selectId].y = col;//ѡ�����ƶ���ȥ
				Stones[clickId].isDead = true;//���㵽������ʱ��ʧ
				map[row][col] = Stones[selectId].value;//������map�м�¼
			}
			

		}


		
		
		


		//��������·��û��ֱ�������ĵ㣬Ҳ����
		//Ҳ�����дһ������A��B�㣬�����ܲ���ֱ�

		//���ȹ�ȥ
		
		//���ƶ��Ĺ��ɶ���
		//��һ��canMove
		selectId = -1;
		update();
	}

}




BoardTobattle::~BoardTobattle()
{}