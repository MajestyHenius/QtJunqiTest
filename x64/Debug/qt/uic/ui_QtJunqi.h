/********************************************************************************
** Form generated from reading UI file 'QtJunqi.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTJUNQI_H
#define UI_QTJUNQI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtJunqiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtJunqiClass)
    {
        if (QtJunqiClass->objectName().isEmpty())
            QtJunqiClass->setObjectName(QString::fromUtf8("QtJunqiClass"));
        QtJunqiClass->resize(600, 400);
        menuBar = new QMenuBar(QtJunqiClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtJunqiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtJunqiClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtJunqiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtJunqiClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtJunqiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtJunqiClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtJunqiClass->setStatusBar(statusBar);

        retranslateUi(QtJunqiClass);

        QMetaObject::connectSlotsByName(QtJunqiClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtJunqiClass)
    {
        QtJunqiClass->setWindowTitle(QCoreApplication::translate("QtJunqiClass", "QtJunqi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtJunqiClass: public Ui_QtJunqiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTJUNQI_H
