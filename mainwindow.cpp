#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    length=0;
    blockH = 671;
    blockW = 20;
    data = new double [1000];
    flag = 1;
    cur = 0;
    thread = new QThread(this);
    time = 1000;
    QRegExp regx("[0-9\\s]+$");
    QValidator *validator = new QRegExpValidator(regx);
    ui->lineEdit->setValidator(validator);
}
void MainWindow::paintEvent(QPaintEvent *)//绘图
{
    QPainter painter;
    if(data == nullptr)
        return ;
    QFont font1("微软雅黑",8,QFont::Bold,true);
    painter.begin(this);
    for(int i = 0; i < length;i++){
        QRect rect(i*blockW,height()-data[i]/100*blockH,blockW-1,blockH*data[i]);//绘制矩形高度（x,y,w,h)
        if(i == cur){
            painter.fillRect(rect,Qt::blue);
        }else {
            painter.fillRect(rect,Qt::red);
        }
        QString d = QString::number(data[i]);
        painter.setFont(font1);
        painter.drawText(i*blockW,height()-data[i]/100*blockH,d);
    }
    painter.end();
}

void MainWindow::deal(int c)//进行重绘
{
    cur = c;
    repaint();
}

MainWindow::~MainWindow()
{
    delete [] data;
    thread->quit();     //结束子线程
    thread->wait();     //回收子线程资源
    delete ui;
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    speed(index);
}
void MainWindow::on_lineEdit_editingFinished()//文本框数据处理
{
    QString s = ui->lineEdit->text();
    s =s.simplified();
    QStringList list = s.split(" ");
    length = list.size();
    for (int i = 0; i < list.size(); i++)
    {
        data[i] = list[i].toInt();
    }
}

//槽函数
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
    quicksort();
}

void MainWindow::on_pushButton_4_clicked()//重排
{

    ui->lineEdit->setText("");
    delete [] data;
}
void MainWindow::on_radioButton_clicked()//升序
{
    flag = 1;
    changes();
}

void MainWindow::on_radioButton_2_clicked()//降序
{
    flag=0;
    changes();
}

void MainWindow::on_pushButton_5_clicked()
{
    insertsort();
}

void MainWindow::on_pushButton_6_clicked()
{
    mergesort();
}


//函数接口

void MainWindow::bubblesort()//冒泡排序
{
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goBubble);
    bubble->moveToThread(thread);
    thread->start(); //开启子线程
    emit start();   //运行子线程的go函数

}
void MainWindow::selectsort()//选择排序
{
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goselect);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}
void MainWindow::changes()//改变顺序
{
    if(ui->lineEdit->text()!="")
    {
        delete bubble;
        QString s = ui->lineEdit->text();
        s =s.simplified();
        QStringList list = s.split(" ");
        length = list.size();
        for (int i = 0; i < list.size(); i++)
           data[i] = list[i].toInt();
    }
}


void MainWindow::quicksort()//快速排序
{
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goquick);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}


void::MainWindow::speed(int index)//改变速度
{
    if(index==1)
    {
        bubble->mDelay=250;
    }
    if(index==2)
    {
        bubble->mDelay=80;
    }
    if(index==0)
    {
        bubble->mDelay=400;
    }
}


void MainWindow::insertsort()
{
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goinsert);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::mergesort()
{
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::gomerge);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}
