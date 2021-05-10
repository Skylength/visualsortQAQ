#include "mainwindow.h"

#include <QVector>
#include <QTime>    //方便产生随机数
#include <QThread>    //多线程
#include <QDebug>    //方便调试打印
#include <QPainter>    //绘图
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
