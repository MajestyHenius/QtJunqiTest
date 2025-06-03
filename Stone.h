#pragma once
#include <QObject>
class Stone  : public QObject
{
	Q_OBJECT

public:
	Stone(QObject* parent = nullptr) : QObject(parent) {}
	//Stone() : Stone(nullptr) {}
	int stoneId;
	int value;//ս������40��39...
	bool visible;//�Ƿ���������ָ���죬�Լ�һ��ʼ��
	bool canMove = false;//�Ƿ��ܶ������ף��Լ�һ��ʼ��
	bool isDead = false;//�Ƿ���ʧ
	bool isRed = true;//�����ֻ��Ǻ��֡������Ǻ�ɫ����������ɫ
	int x, y;//��������꣬����ת��Ϊʵ�ʵ�QPointλ��
	QString getText()
	{
		switch (this->value)
		{
		case 40:
			return QString::fromLocal8Bit("˾��");
		case 39:
			return QString::fromLocal8Bit("����");
		case 38:
			return QString::fromLocal8Bit("ʦ��");
		case 37:
			return QString::fromLocal8Bit("�ó�");
		case 36:
			return QString::fromLocal8Bit("�ų�");
		case 35:
			return QString::fromLocal8Bit("Ӫ��");
		case 34:
			return QString::fromLocal8Bit("����");
		case 33:
			return QString::fromLocal8Bit("�ų�");
		case 32:
			return QString::fromLocal8Bit("����");
		case 0:
			return QString::fromLocal8Bit("ը��");
		case -1:
			return QString::fromLocal8Bit("����");
		case 41:
			return QString::fromLocal8Bit("����");
		}
		return "�㿪����!";
	}//�������֣�������ʾ

	bool readEmbattled();//���ļ��ж�ȡ���֣������

	void init(int id)
	{
		struct {
			int x, y;
			int value;
		}pos[25] = {//���־��������ʽȥ����д�����д����顣
			{1,1,41},
			{1,2,-1},
			{1,3,41},
			{1,4,33},
			{1,5,41},
			{2,1,36},
			{2,2,32},
			{2,3,35},
			{2,4,32},
			{2,5,36},
			{3,1,0},
			{3,3,34},
			{3,5,35},
			{4,1,37},
			{4,2,33},
			{4,4,33},
			{4,5,0},
			{5,1,39},
			{5,3,34},
			{5,5,37},
			{6,1,40},
			{6,2,32},
			{6,3,38},
			{6,4,33},
			{6,5,38},
		};


		stoneId = id;
		isDead = false;
		isRed = stoneId < 25;//ǰ25�������ֺ�ɫ��
		if (id < 25)
		{
			visible = false;
			x = pos[id].x;
			y = pos[id].y;
			value = pos[id].value;
		}
		else//��ʱ�Գƻ�����ʵӦ�ö����ߵı�20240925��֮��Ҫ������ģʽ�и��ģ���ȡ˫���ı�,�Լ�������׶μ�¼���
		{
			visible = true;
			x = 13-pos[id-25].x;
			y = pos[id-25].y;
			value = pos[id-25].value;
		}

	}
	void playerChange(int id);
	//Stone(bool isFirst)
	~Stone();
};
