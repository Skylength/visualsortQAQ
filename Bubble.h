#ifndef BUBBLE_H
#define BUBBLE_H

#include <QObject>
#include <QThread>
#include <QTime>
class Bubble : public QObject
{
    Q_OBJECT
public:

    explicit Bubble(int time,int flag,int l,int m,double *data,QObject *parent = nullptr);
    void goBubble();      //处理排序算法
    void goselect();
    void goinsert();
    void goquick();
    void quicksort(int mins,int maxs);
    void swap(int i,int j);
    int quickprocess(int mins,int maxs);
    void mergeSort(int L,int R);
    void merge(int L,int M,int R);
    void gomerge();
    void speeds(int value);
    int mDelay;  //延时时间，方便动态展示
signals:
    void bubbleSignal(int cur); //发送当前排序的位子
    void end();
private:
    int length;     //数组的长度
    double *data;      //数组
    int max;        //单个数据的最大值
    int cur;        //排序当前处理的位置
    int mins;
    int maxs;
    int f;   //判断顺序
    int L,R,M;

public slots:

};

#endif // BUBBLE_H
