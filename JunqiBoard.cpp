#include "JunqiBoard.h"
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QtCore/QDebug>//debug�����
//#include <QBasicTimer>//��ʱ������˸Ч��
JunqiBoard::~JunqiBoard()
{

}

bool JunqiBoard::getRowCol(QPoint pt, int& row, int& col)
{

	//���ӵ������� (hori * j * pWidth) - stoneWidth / 2 ;(i)*pLength - stoneHeight / 2, stoneWidth, stoneHeight�� ����i,j
	int xPos = pt.rx();//x��������ã���������Ϊ�������ܶ����޸ġ�
	int yPos = pt.ry();
	col = (xPos + stoneWidth / 2) / hori / pWidth; //��������������i��j
	row = (yPos + stoneHeight / 2);//row����
	row = row / pLength;
	int deltx = abs(xPos - (hori * col * pWidth - stoneWidth / 2));
	int delty = abs(yPos - (row * pLength - stoneHeight / 2));
	bool isInBoard;
	isInBoard = (deltx <= (stoneWidth)) && (delty <= (stoneHeight));
	//���򲻳������߳�
	//���򲻳�����߳�
	//�����������true

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
	QPen road = painter.pen();//��·��ϸ�ߣ���ӦĬ�ϱ�ˢ
	QPen campLine(Qt::red, 2);//��Ӫ������
	QBrush campBrush(Qt::white, Qt::SolidPattern);//��Ӫ���
	QPen stationLine(Qt::black, 2);//��Ӫ����
	QBrush stationBrush(Qt::white, Qt::SolidPattern);//��Ӫ���

	QPen rail(Qt::black, 3, Qt::DashLine);//��·�ֵĺڰ����
	QVector<qreal> dashPattern = { 2, 2 }; // ÿ2��������ʾ2�����ص�ʵ�ߣ���·
	
	rail.setDashPattern(dashPattern);
	for (int i = 1; i <= 6; ++i)//����6����
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
	//��һ��ɽ��
	for (int i = 7; i <= 12; ++i)
	{
		if (i == 7 || i == 11)
		{
			painter.setPen(rail);//������·
		}
		else
		{
			painter.setPen(road);//���๫·
		}
		painter.drawLine(QPoint(hori *pWidth, (mountSize+i) * pLength), QPoint((hori*5) * pWidth, (mountSize+i) * pLength));
	}
	//����
	for (int i = 1; i <= 5; ++i)
	{
		if (i == 1 || i == 5)
		{
			//������·
			painter.setPen(rail);
			painter.drawLine(QPoint(hori * i * pWidth, 2*pLength), QPoint(hori * i * pWidth, (12+ mountSize-1) * pLength));
			painter.setPen(road);
			painter.drawLine(QPoint(hori * i * pWidth, 1 * pLength), QPoint(hori * i * pWidth, 2 * pLength));//����� 5�е����ߵ�һ����·
			painter.drawLine(QPoint(hori * i * pWidth, (12 + mountSize - 1) * pLength), QPoint(hori * i * pWidth, (12 + mountSize ) * pLength));//����� 5�е����ߵ�һ����·
		}
		else if (i == 3)
		{
			//�м���·
			painter.setPen(road);
			painter.drawLine(QPoint(hori * 3 * pWidth, 1 * pLength), QPoint(hori * 3 * pWidth, 6 * pLength));
			painter.drawLine(QPoint(hori * 3 * pWidth, (7 + mountSize) * pLength), QPoint(hori * 3 * pWidth, (12 +mountSize) * pLength));
			painter.setPen(rail);
			painter.drawLine(QPoint(hori * 3 * pWidth, 6 * pLength), QPoint(hori * 3 * pWidth, (7+mountSize) * pLength));
		}
		else
		{
			//���๫·
			painter.setPen(road);
			painter.drawLine(QPoint(hori*i*pWidth, pLength), QPoint(i * pWidth, 6 * pLength));
			painter.drawLine(QPoint(hori*i*pWidth,(7+ mountSize)*pLength), QPoint(i * pWidth, (12 + mountSize) * pLength));
		}

	}
	//б��·��
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
	//����վ����Ӫ����Ӫ
	for (int i = 1; i <= 12; i++)//12��
	{
		for (int j = 1; j <= 5; j++)//5��
		{
			if ((i == 3 && j == 2) || (i == 3 && j == 4) || (i == 4 && j == 3) || (i == 5 && j == 2) || (i == 5 && j == 4))
			{ 
				//������Ӫ
				painter.setPen(campLine);
				painter.setBrush(campBrush);
				painter.drawEllipse(j * hori* pWidth - campRadius, i* pLength - campRadius, 2 * campRadius, 2 * campRadius);
			}
			else if ((i == 8 && j == 2) || (i == 8 && j == 4) || (i == 9 && j == 3) || (i == 10 && j == 2) || (i == 10 && j == 4))
			{
				//�Բ���Ӫ
				painter.setPen(campLine);
				painter.setBrush(campBrush);
				painter.drawEllipse(j * hori * pWidth - campRadius, (i + mountSize) * pLength - campRadius, 2 * campRadius, 2 * campRadius);
			}
			else if ((i == 1 && j == 2)|| (i == 1 && j == 4))
			{
				//�����Ӫ
				painter.setPen(stationLine);
				painter.setBrush(stationBrush);
				painter.drawRect((hori * j * pWidth) - headSize *stationWidth / 2, (i)*pLength - headSize *stationHeight / 2, headSize *stationWidth, headSize *stationHeight);
			}
			else if ((i == 12 && j == 2) || (i == 12 && j == 4))
			{
				//�Բ��Ӫ
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
					//��ͨ��վ�Բ�
					painter.drawRect((hori * j * pWidth) - stationWidth / 2, (i + mountSize) * pLength - stationHeight / 2, stationWidth, stationHeight);
				}
				else
				{
					//��ͨ��վ����
					painter.drawRect((hori * j * pWidth) - stationWidth / 2, (i)*pLength - stationHeight / 2, stationWidth, stationHeight);
				}
			}
			
			
		}
	}

	//��������
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
	//�ȳ�ʼ��������ɫ��ˢ
	QPen stonePenRed(Qt::black, 2);//��ɫ�߿�
	QBrush stoneBrushRed(Qt::yellow, Qt::SolidPattern);//���
	QPen stonePenBlue(Qt::black, 2);//��ɫ�߿�
	QBrush stoneBrushBlue(Qt::cyan, Qt::SolidPattern);//���
	QBrush stoneBrushGray(Qt::gray, Qt::SolidPattern);//��ѡ���ǻ�ɫ
	int j = Stones[id].y;//��
	int i = Stones[id].x;//��

	//int j = animatedY;//��
	//int i = animatedX;//��

	QRect rect;

	if (i < 7)//�����棬������
	{
		rect = QRect((hori * j * pWidth) - stoneWidth / 2, (i)*pLength - stoneHeight / 2, stoneWidth, stoneHeight);
	}
	else    //����ߣ���Ҫ��һ��ɽ��ľ���
	{
		rect = QRect((hori * j * pWidth) - stoneWidth / 2, (i + mountSize) * pLength - stoneHeight / 2, stoneWidth, stoneHeight);
	}
	

	if (id < 25)//���������
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
			painter.setBrush(stoneBrushGray);;//ѡ�а�͸��Ч��
		}
		else
		{
			painter.setBrush(stoneBrushBlue);
		}
		//�������ҷ����ӻ��ǶԷ����ӣ������ֻ����ɫ����ɽ������Ӧ��һ����
	
		painter.drawRect(rect);
		painter.setFont(QFont(QString::fromLocal8Bit("����"), 10, -1, false));
		//painter.setPen(Qt::white);
		painter.drawText(rect, Stones[id].getText(), QTextOption(Qt::AlignCenter));
		
	}
}


