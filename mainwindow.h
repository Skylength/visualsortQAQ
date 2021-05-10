#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Bubble.h"
#include <QPainter>
#include <QMutexLocker>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
signals:
    void start();       //开启子线程
    void shunxu();
public slots:
    void deal(int); //处理来自子线程的消息
private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int flag;
    int blockH;     //绘图方块的高
    int blockW;     //绘图方块的宽
    int length;     //数组长度
    int *data;      //数组
    int cur;        //当前排序的位子
    int pause;
    QThread *thread;
    Bubble *bubble;
};

#endif // WIDGET_H
