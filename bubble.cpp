#include "Bubble.h"
#include <QDebug>

Bubble::Bubble(int l, int m, int *data, QObject *parent) :
    QObject(parent)
{
    length = l;
    max = m;
    mDelay = 1000;//延时时间
    this->data = data;

}

void Bubble::goBubble()
{
    bool flag = false;  //供判断是否已经完成
    for(int i = 1; i < length && !flag; i ++)
    {
        flag = true;
        for(int j = 0; j < length-i; j++)
        {
            if(data[j] < data[j+1])
            {
                int t = data[j];
                data[j] = data[j+1];
                data[j+1] = t;
                flag = false;
            }
            bubbleSignal(j);
            QThread::msleep(static_cast<unsigned int>(mDelay));//完成一次交换，进行一次排序
        }
    }
    for(int i = 0; i < length; i++)//排序完成后定标进入最大值
    {
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }

}
void Bubble::goBubble1()
{
    bool flag = false;  //供判断是否已经完成
    for(int i = 1; i < length && !flag; i ++)
    {
        flag = true;
        for(int j = 0; j < length-i; j++)
        {
            if(data[j] > data[j+1])
            {
                int t = data[j];
                data[j] = data[j+1];
                data[j+1] = t;
                flag = false;
            }
            bubbleSignal(j);
            QThread::msleep(static_cast<unsigned int>(mDelay));//完成一次交换，进行一次排序
        }
    }
    for(int i = 0; i < length; i++)//排序完成后定标进入最大值
    {
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
}
void Bubble::goselect()//选择
{
    int i,j,index,temp;
    for(i=0;i<length-1;i++)  //最外层遍历
    {
        index=i;//无序区的第一位
        for(j=i+1;j<length;j++) //开始找无序区的最小元素
            if(data[j]<data[index] )
            index=j;   //记录最小值
        if(index!=i)
        {
          temp=data[i];
          data[i]=data[index];
          data[index]=temp; //将最小值放到有序区中
          bubbleSignal(i);
          QThread::msleep(static_cast<unsigned int>(mDelay));
        }
    }
    for(int i = 0; i < length; i++)//排序完成后定标进入最大值
    {
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
}

//快速排序
void Bubble::goquick()
{
    quicksort(0,length-1);      //进行快排
    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
}
int Bubble::quickprocess(int mins,int maxs)
{
    int t = data[mins];

    while(mins<maxs)
    {
        while(mins<maxs&&data[maxs]>=t)
            maxs--;
        swap(mins,maxs);
        while(mins<maxs&&data[mins]<=t)
            mins++;
        swap(mins,maxs);
    }
    return mins;
}
void Bubble::quicksort(int mins,int maxs)
{
    if(mins<maxs)
    {
        int flag = quickprocess(mins,maxs);
        quicksort(mins,flag);
        quicksort(flag+1,maxs);
    }
}
void Bubble::swap(int i,int j)
{
    int temp=data[i];
    data[i]=data[j];
    data[j]=temp;
    bubbleSignal(i);
    QThread::msleep(static_cast<unsigned int>(mDelay));
}


