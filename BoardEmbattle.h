
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
			Stones[i].init(i);//��ʼ��
			selectId = -1;
		}
	};
	~BoardEmbattle();
	void mouseReleaseEvent(QMouseEvent* event);//�ʺϴ����¼���ͬ���ŵ�������
};
