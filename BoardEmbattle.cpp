#include "BoardEmbattle.h"
#include <QMouseEvent>
#include <QtCore/QDebug>//debug�����
//ֻ�ܲ��֣��̳���������


BoardEmbattle::~BoardEmbattle()
{}


void BoardEmbattle::mouseReleaseEvent(QMouseEvent* event)//�ʺϴ����¼���ͬ���ŵ�������
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
		if (Stones[i].x == row && Stones[i].y == col)
		{
			//˵��������ӱ�ѡ����
			if (row > 6)
			{
				qDebug() << row << "," << col << QString::fromLocal8Bit("��ѡ��");
				break;
			}
		}
	}
	if (i >= 25 && i < 50)//�����±���ҵ�
	{
		//if(row!=)//����ѡ��ĵ������Ӱ�
		clickId = i;
	}

	if (selectId == -1)//��һ�ε��
	{
		qDebug() << QString::fromLocal8Bit("�㵽��һ������");
		if (clickId != -1)//�㵽һ������
		{
			selectId = clickId;
			update();
		}
	}
	else//�´ε��
	{
		qDebug() << QString::fromLocal8Bit("�㵽�ڶ�������");
		if (clickId != -1)//�ֵ㵽һ������
		{
			//ը�������ڵ�һ��:
			if ((Stones[selectId].value == 0 && row < 8) || (Stones[clickId].value == 0 && Stones[selectId].x < 8))
			{
				//selectId = -1;
				qDebug() << QString::fromLocal8Bit("ը�����ܷŵ�һ��");
			}
			//���ײ�����1 - 4�ţ����岻�ܳ���Ӫ
			else if ((Stones[selectId].value == 41 && row < 11) || (Stones[clickId].value == 41 && Stones[selectId].x < 11))
			{
				qDebug() << QString::fromLocal8Bit("ը�����ܷŵ�5����ǰ");
			}
			else if ((Stones[selectId].value == -1 && row != 6 && (col != 2 && col != 4)) ||
				(Stones[clickId].value == -1 && Stones[selectId].x != 6 && (Stones[selectId].y != 2 && Stones[selectId].y != 4)))
			{
				qDebug() << QString::fromLocal8Bit("���첻�ܷ��ڴ�Ӫ��");
			}
			else
			{
				Stones[clickId].x = Stones[selectId].x;
				Stones[clickId].y = Stones[selectId].y;//������ӽ���
				Stones[selectId].x = row;
				Stones[selectId].y = col;

			}
			selectId = -1;
			update();
		}
	}

}