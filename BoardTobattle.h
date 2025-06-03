
#include "JunqiBoard.h"
#include <QMouseEvent>
#include <QQueue>
#include <QTimer>
class BoardTobattle  : public JunqiBoard
{
	Q_OBJECT

public:
	


	BoardTobattle(QWidget* parent = nullptr) : JunqiBoard(parent)
	{
		for (int i = 0; i < 50; i++)
		{
			Stones[i].init(i);//��ʼ��
			selectId = -1;
		} 
		animationTimer = new QTimer(this);
		connect(animationTimer, &QTimer::timeout, this, &BoardTobattle::updateAnimation);



	};
	~BoardTobattle();

	
		
		





	int g[11][5];//ͼ��ʾ��·��ͨ�ԣ���map��̫һ�������Ǻܺ����á�
	int dist[11][5];//����
	QPoint parent[11][5];//���ڼ�¼ǰ����	
	QVector<QPoint> route;//���ڱ��湤��������·��
	QTimer* timer; //�ƶ��õĶ�ʱ��
	void mouseReleaseEvent(QMouseEvent* event);//�ʺϴ����¼���ͬ���ŵ�������
	bool canMove(int fromRow, int fromCol, int toRow, int toCol);//�ж��ܷ����塣
	bool isOnRail(int row, int col);//�Ƿ���������
	bool clearRowPath(int Row, int fromCol, int toCol);//���Ƿ����ڵ���ͨ��
	bool clearColPath(int Col,int fromRow, int toRow);//���Ƿ����ڵ���ͨ��
	int BFS_Engineer(int fromRow, int fromCol, int toRow, int toCol);//��������BFS�㷨
	void moveAnimation(int fromRow, int fromCol, int toRow, int toCol);//�ƶ����Ŷ���
	void updateAnimation();
private:
	QTimer* animationTimer; // ��ʱ��
	int animationStep; // ��������
	int startx, starty; // ��ʼλ��
	int endx, endy; // Ŀ��λ��


};
