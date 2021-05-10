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
    data = new int [1000];
    flag = 1;
    cur = 0;
    thread = new QThread(this);

}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    if(data == nullptr)
        return ;
    QFont font1("微软雅黑",8,QFont::Bold,true);
    painter.begin(this);
    for(int i = 0; i < length;i++){
        QRect rect(i*blockW,height()-data[i]*blockH,
                   blockW - 1,data[i]*blockH);//绘制矩形高度

        if(i == cur){
            painter.fillRect(rect,Qt::blue);
        }else {
            painter.fillRect(rect,Qt::red);
        }
        QString d = QString::number(data[i]);
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

void MainWindow::on_lineEdit_editingFinished()//文本框数据处理
{

    QString s = ui->lineEdit->text();
    QStringList list = s.split(" ");
    length = list.size();
    for (int i = 0; i < list.size(); i++)
       data[i] = list[i].toInt();
}

void MainWindow::on_pushButton_clicked()//冒泡排序
{
    bubblesort();
}


void MainWindow::on_pushButton_3_clicked()//选择排序
{
    selectsort();
}

void MainWindow::on_pushButton_2_clicked()//快速排序
{

    bubble = new Bubble(flag,length,length,data);

    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goquick);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::on_pushButton_4_clicked()//重排
{

    ui->lineEdit->setText("");
    delete [] data;
}

void MainWindow::on_radioButton_2_clicked()
{
    changes();
}
void MainWindow::bubblesort()
{
    bubble = new Bubble(flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goBubble);
    bubble->moveToThread(thread);
    thread->start(); //开启子线程
    emit start();   //运行子线程的go函数

}
void MainWindow::selectsort()
{
    bubble = new Bubble(flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goselect);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}
void MainWindow::changes()
{

    delete bubble;
    flag = 0;
    qDebug()<<flag;
    QString s = ui->lineEdit->text();
    QStringList list = s.split(" ");
    length = list.size();
    for (int i = 0; i < list.size(); i++)
       data[i] = list[i].toInt();
}

void MainWindow::on_radioButton_clicked()
{
    flag = 1;
}
