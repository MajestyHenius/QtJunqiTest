
#include "JunqiBoard.h"
#include <QMouseEvent>
class BoardEmbattle  : public JunqiBoard
{
	Q_OBJECT

public:
	BoardEmbattle(QWidget* parent = nullptr) : JunqiBoard(parent)
	{
		for (int i = 0; i < 50; i++)
		{
			Stones[i].init(i);//初始化
			selectId = -1;
		}
	};
	~BoardEmbattle();
	void mouseReleaseEvent(QMouseEvent* event);//适合处理事件不同，放到子类中
};
