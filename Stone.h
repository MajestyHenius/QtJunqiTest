#pragma once
#include <QObject>
class Stone  : public QObject
{
	Q_OBJECT

public:
	Stone(QObject* parent = nullptr) : QObject(parent) {}
	//Stone() : Stone(nullptr) {}
	int stoneId;
	int value;//战斗力，40，39...
	bool visible;//是否能亮（特指军旗，以及一开始）
	bool canMove = false;//是否能动（地雷，以及一开始）
	bool isDead = false;//是否消失
	bool isRed = true;//是先手还是后手。先手是红色，后手是蓝色
	int x, y;//抽象的坐标，可以转化为实际的QPoint位置
	QString getText()
	{
		switch (this->value)
		{
		case 40:
			return QString::fromLocal8Bit("司令");
		case 39:
			return QString::fromLocal8Bit("军长");
		case 38:
			return QString::fromLocal8Bit("师长");
		case 37:
			return QString::fromLocal8Bit("旅长");
		case 36:
			return QString::fromLocal8Bit("团长");
		case 35:
			return QString::fromLocal8Bit("营长");
		case 34:
			return QString::fromLocal8Bit("连长");
		case 33:
			return QString::fromLocal8Bit("排长");
		case 32:
			return QString::fromLocal8Bit("工兵");
		case 0:
			return QString::fromLocal8Bit("炸弹");
		case -1:
			return QString::fromLocal8Bit("军旗");
		case 41:
			return QString::fromLocal8Bit("地雷");
		}
		return "你开挂了!";
	}//棋子名字，用来显示

	bool readEmbattled();//从文件中读取布局，待完成

	void init(int id)
	{
		struct {
			int x, y;
			int value;
		}pos[25] = {//布局就用这个格式去读、写。还有错误检查。
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
		isRed = stoneId < 25;//前25个是先手红色？
		if (id < 25)
		{
			visible = false;
			x = pos[id].x;
			y = pos[id].y;
			value = pos[id].value;
		}
		else//暂时对称画，其实应该读两边的表，20240925：之后要在联机模式中更改，读取双方的表,以及，摆棋阶段记录表格。
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
