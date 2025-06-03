#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtJunqi.h"

class QtJunqi : public QMainWindow
{
    Q_OBJECT

public:
    QtJunqi(QWidget *parent = nullptr);
    ~QtJunqi();

private:
    Ui::QtJunqiClass ui;
};
