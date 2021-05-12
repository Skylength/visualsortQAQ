#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QRegExpValidator>
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
    begin=0;
    thread = new QThread(this);
    time = ui->horizontalSlider->value();



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

void MainWindow::on_lineEdit_editingFinished()//文本框数据处理
{
    if(begin!=1)
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
}

//槽函数
void MainWindow::on_pushButton_clicked()//冒泡排序
{
    bubblesort();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if(begin)
    {
        this->bubble->mDelay=value;
    }
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

void MainWindow::on_pushButton_5_clicked()//插入排序
{
    insertsort();
}

void MainWindow::on_pushButton_6_clicked()//归并排序
{
    mergesort();
}


//函数接口
void MainWindow::release()//解除禁用
{
    delete bubble;
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    begin=0;
}

void MainWindow::ban()//禁用按钮
{
    begin=1;
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);

}

void MainWindow::bubblesort()//冒泡排序
{
    ban();
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goBubble);
    connect(bubble,&Bubble::end,this,&MainWindow::release);
    bubble->moveToThread(thread);
    thread->start(); //开启子线程
    emit start();   //运行子线程的go函数

}

void MainWindow::selectsort()//选择排序
{
    ban();
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goselect);
    connect(bubble,&Bubble::end,this,&MainWindow::release);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::changes()//改变顺序
{
    if(ui->lineEdit->text()!="")
    {
        if(begin)
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
    ban();
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goquick);
    connect(bubble,&Bubble::end,this,&MainWindow::release);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::insertsort()//插入排序
{
    ban();
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::goinsert);
    connect(bubble,&Bubble::end,this,&MainWindow::release);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

void MainWindow::mergesort()//归并排序
{
    ban();
    bubble = new Bubble(time,flag,length,length,data);
    connect(bubble,&Bubble::bubbleSignal,this,&MainWindow::deal);
    connect(this,&MainWindow::start,bubble,&Bubble::gomerge);
    connect(bubble,&Bubble::end,this,&MainWindow::release);
    bubble->moveToThread(thread);
    thread->start();
    emit start();
}

