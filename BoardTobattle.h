
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
			Stones[i].init(i);//初始化
			selectId = -1;
		} 
		animationTimer = new QTimer(this);
		connect(animationTimer, &QTimer::timeout, this, &BoardTobattle::updateAnimation);



	};
	~BoardTobattle();

	
		
		





	int g[11][5];//图表示铁路连通性，和map不太一样，不是很好沿用。
	int dist[11][5];//距离
	QPoint parent[11][5];//用于记录前驱。	
	QVector<QPoint> route;//用于保存工兵的行走路径
	QTimer* timer; //移动用的定时器
	void mouseReleaseEvent(QMouseEvent* event);//适合处理事件不同，放到子类中
	bool canMove(int fromRow, int fromCol, int toRow, int toCol);//判断能否走棋。
	bool isOnRail(int row, int col);//是否在铁轨上
	bool clearRowPath(int Row, int fromCol, int toCol);//横是否无遮挡畅通。
	bool clearColPath(int Col,int fromRow, int toRow);//纵是否无遮挡畅通。
	int BFS_Engineer(int fromRow, int fromCol, int toRow, int toCol);//给工兵的BFS算法
	void moveAnimation(int fromRow, int fromCol, int toRow, int toCol);//移动播放动画
	void updateAnimation();
private:
	QTimer* animationTimer; // 定时器
	int animationStep; // 动画步骤
	int startx, starty; // 起始位置
	int endx, endy; // 目标位置


};
