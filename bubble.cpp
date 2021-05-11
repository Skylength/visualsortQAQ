#include "Bubble.h"
#include <QDebug>

Bubble::Bubble(int time,int flag,int l, int m, int *data, QObject *parent) :
    QObject(parent)
{
    length = l;
    max = m;
    mDelay = time;//延时时间
    this->data = data;
    f = flag;
}

void Bubble::goBubble()
{

    bool flag = false;  //供判断是否已经完成
    for(int i = 1; i < length && !flag; i ++)
    {
        flag = true;
        for(int j = 0; j < length-i; j++)
        {
            bubbleSignal(j);
            QThread::msleep(static_cast<unsigned int>(mDelay));
            if(f==1)
            {

                if(data[j] > data[j+1])
                {
                    int t = data[j];
                    data[j] = data[j+1];
                    data[j+1] = t;
                    flag = false;
                }
            }
            if(f==0)
            {
                bubbleSignal(j);
                QThread::msleep(static_cast<unsigned int>(mDelay));
                if(data[j] < data[j+1])
                {
                    int t = data[j];
                    data[j] = data[j+1];
                    data[j+1] = t;
                    flag = false;
                }
            }
        }
    }
    for(int i = 0; i < length; i++){
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
        {
            if(f==1)
            {
                if(data[j]<data[index] )
                    index=j;   //记录最小值
            }
            if(f==0)
            {
                if(data[j]>data[index] )
                    index=j;   //记录最小值
            }
        }
        if(index!=i)
        {
          bubbleSignal(i);
          QThread::msleep(static_cast<unsigned int>(mDelay));
          temp=data[i];
          data[i]=data[index];
          data[index]=temp; //将最小值放到有序区中
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
    if(f==1)
    {
        while(mins<maxs)
        {
            while(mins<maxs&&data[maxs]>=t)
                maxs--;
            swap(mins,maxs);
            while(mins<maxs&&data[mins]<=t)
                mins++;
            swap(mins,maxs);
        }
    }
    if(f==0)
    {
        while(mins<maxs)
        {
            while(mins<maxs&&data[maxs]<=t)
                maxs--;
            swap(mins,maxs);
            while(mins<maxs&&data[mins]>=t)
                mins++;
            swap(mins,maxs);
        }
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
    bubbleSignal(i);
    QThread::msleep(static_cast<unsigned int>(mDelay));
    int temp=data[i];
    data[i]=data[j];
    data[j]=temp;

}

