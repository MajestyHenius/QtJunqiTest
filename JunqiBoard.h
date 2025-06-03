#pragma once
#include <QtCore/QDebug>//debug�����
#include <QWidget>
#include "Stone.h"
class JunqiBoard  : public QWidget
{
	Q_OBJECT

public:
	//QMap<int,QMap<int, Stone&>>map;//��x��yλ�ô������ӵ�����
	QMap<int, QMap<int, int>>map; //��1��1��ʼ�Ķ�̬�ռ䣬��m�е�n�оͶ�Ӧm, n
	//int map[13][6];//����������һȦ�հ��а�ȫ�У��ҵ�m�е�n�оͶ�Ӧm,n
	//QMap<int, QMap<int, int>>distance;//�洢�����
	int selectId;//����ѡ�����ӵ�id
	bool pendingChange;//��Ҫ�ȴ���һ���������Խ���
	int pWidth = 80, pLength = 40;//��Ϊ�ǳ�������Ļ�����λ
	int vert = 16, hori = 1.2;//��ֱ��ˮƽ���򣬻�����λ����ı���
	int stationWidth = pWidth / 3, stationHeight = pLength / 3;//��վ��ȳ���
	int stoneWidth = pWidth / 5*2, stoneHeight = pLength / 2;//���ӿ�ȳ���
	int campRadius = 18;//��ӪԲȦ�İ뾶
	float headSize = 2;//��Ӫ��С�Ǳ�վ�Ķ��ٱ�
	int mountSize = 3;//ɽ�糤��
	Stone Stones[50];//���ӣ�ǰ25Ϊ�Է�

	JunqiBoard(QWidget* parent = nullptr) : QWidget(parent)
	{
		//�ȸ����е�λ��ֵ99
		for (int i = 1; i <= 12; i++)
		{
			for (int j = 1; j <= 5; j++)
			{
				map[i][j] = 99;//99��ʾû����
			}
		}
		//�ٰ����ָ���վλ�ø�ֵ
		for (int i = 0; i < 50; i++)
		{
			Stones[i].init(i);//��ʼ��
			map[Stones[i].x][Stones[i].y] = Stones[i].value;
			selectId = -1;
		}
		//������debug�ã����λ���Ƿ���ȷ��
		printBoard();

		
		
		//�����ﻹ��Ҫ��map�ĳ�ʼ��
	};
	
	bool getRowCol(QPoint pt, int& row, int& col);//������������ڼ��еڼ��г�������

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

	void drawStone(QPainter& painter, int id);//��������
	void paintEvent(QPaintEvent*);//��������
	//void mouseReleaseEvent(QMouseEvent*);//����ͷŲ�����һ����Ϊ�ͷź����Ч��һֱ���Ų���
	virtual ~JunqiBoard();
public:
	float animatedX; // �����е�Xλ��
	float animatedY; // �����е�Yλ��

};