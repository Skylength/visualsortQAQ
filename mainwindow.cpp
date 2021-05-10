#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QWaitCondition>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    length=0;
    blockH = 20;
    blockW = 20;
    data = new int [length];
    cur = 0;
    flag = 0;

    //进行信号与槽的绑定
        //开启子线程
     //运行子线程的goBubble函数
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    QFont font1("微软雅黑",10,QFont::Bold,true);
    if(data == nullptr)
        return;
    painter.begin(this);
    for(int i = 0; i < length;i++){
        QRect rect(i*blockW,height()-data[i]*blockH,
                   blockW - 1,data[i]*blockH);//绘制矩形高度
        QString d = QString::number(data[i]);
        if(i == cur){
            painter.fillRect(rect,Qt::blue);
        }else {
            painter.fillRect(rect,Qt::red);
        }
        painter.setFont(font1);
        painter.drawText(rect,d);
    }
    painter.end();
}

void MainWindow::deal(int c)
{
    cur = c;
    repaint();  //进行重绘
}

MainWindow::~MainWindow()
{
    delete [] data;
    thread->quit();     //结束子线程
    thread->wait();     //回收子线程资源
    delete ui;
}

void MainWindow::on_lineEdit_editingFinished()
{

    QString s = ui->lineEdit->text();
    QStringList list = s.split(" ");
    length = list.size();
    for (int i = 0; i < list.size(); i++)
       data[i] = list[i].toInt();

}

void MainWindow::on_pushButton_clicked()//冒泡排序
{
    repaint();
    bubble = new Bubble(length,length,data);
    thread = new QThread(this);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    if(flag == 1)
        connect(this,&MainWindow::start,bubble,&Bubble::goBubble);

    else
        connect(this,&MainWindow::start,bubble,&Bubble::goBubble1);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::on_radioButton_clicked()
{
    flag = 0;
}

void MainWindow::on_pushButton_3_clicked()//选择排序
{
    repaint();
    thread = new QThread(this);
    bubble = new Bubble(length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    if(flag == 1)
        connect(this,&MainWindow::start,bubble,&Bubble::goselect);
    else
        connect(this,&MainWindow::start,bubble,&Bubble::goselect);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::on_pushButton_2_clicked()//快速排序
{
    repaint();
    thread = new QThread(this);
    bubble = new Bubble(length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    if(flag == 1)
        connect(this,&MainWindow::start,bubble,&Bubble::goquick);
    else
        connect(this,&MainWindow::start,bubble,&Bubble::goquick);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}
