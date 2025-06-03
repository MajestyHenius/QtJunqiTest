#include "QtJunqi.h"
#include "JunqiBoard.h"
#include "BoardEmbattle.h"
#include "BoardTobattle.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QtJunqi w;
    //JunqiBoard board;
    BoardTobattle tobattle;
    // w.show();
    tobattle.show();
    return a.exec();
}
