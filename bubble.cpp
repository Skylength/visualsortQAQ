#include "Bubble.h"
#include <QDebug>
#include"mainwindow.h"
Bubble::Bubble(int flag,int l, int m, double *data, QObject *parent) :
    QObject(parent)
{
    length = l;
    max = m;
    mDelay = 240;
    this->data = data;
    f = flag;
}

void Bubble::goBubble()//冒泡
{
    for(int i = 1; i < length; i ++)
    {
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
                }
            }
        }
    }
    for(int i = 0; i < length; i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    emit end();
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
    emit end();
}


void Bubble::goquick()//快速排序
{
    quicksort(0,length-1);      //进行快排
    for(int i = 0; i < length;i++){
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    emit end();
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
//插入排序
void Bubble::goinsert()
{
    for (int i = 1; i < length;i++)
    {
        int j ;
        if(f==1)
        {
            if(data[i] < data[i - 1])
            {
                int temp = data[i];
                for (j = i - 1;j>= 0&&temp < data[j];j--)
                {
                    data[j+1] = data[j];
                    bubbleSignal(j);
                    QThread::msleep(static_cast<unsigned int>(mDelay));
                }
                data[j + 1] = temp;
                bubbleSignal(j);
                QThread::msleep(static_cast<unsigned int>(mDelay));
            }
        }
        if(f==0)
        {
            if(data[i] > data[i - 1])
            {
                int temp = data[i];
                for (j = i - 1;j>=0&&temp>data[j];j--)
                {
                    data[j+1] = data[j];
                    bubbleSignal(j);
                    QThread::msleep(static_cast<unsigned int>(mDelay));
                }
                data[j + 1] = temp;
                bubbleSignal(j);
                QThread::msleep(static_cast<unsigned int>(mDelay));
            }
        }
    }
    for(int i = 0; i < length; i++)//排序完成后定标进入最大值
    {
        bubbleSignal(i);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    emit end();
}
//归并排序
void Bubble::gomerge()
{
     L=0,R=length-1;
     mergeSort(L,R);
     for(int i = 0; i < length; i++)//排序完成后定标进入最大值
     {
         bubbleSignal(i);
         QThread::msleep(static_cast<unsigned int>(mDelay));
     }
     emit end();
}
void Bubble::merge(int L,int M,int R) /*合并函数*/
{
    int left=M-L,right=R-M+1;
    int Left[left],Right[right];
    int i,j,k;
    /*将一个无序数组拆分成两个数组*/
    for( i=L;i<M;i++)
        Left[i-L]=data[i]; /*填充左数组*/
    for(i=M;i<=R;i++)
        Right[i-M]=data[i]; /*填充右数组*/
    /*将两个有序数组合并成一个有序数组*/
    i=0,j=0,k=L;
    /*把两个数组中的元素从小到大依次填入一个主数组*/
    if(f==1)
    {
        while(i<left&&j<right)
        {
            if(Left[i]<Right[j])
                data[k++]=Left[i++];
            else
                data[k++]=Right[j++];
            bubbleSignal(k);
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }
    }
    if(f==0)
    {
        while(i<left&&j<right)
        {
            if(Left[i]>Right[j])
                data[k++]=Left[i++];
            else
                data[k++]=Right[j++];
            bubbleSignal(k);
            QThread::msleep(static_cast<unsigned int>(mDelay));
        }
    }

    /*将剩下未填完的一个数组的元素赋给主数组*/
    while(i<left)
    {
        data[k++]=Left[i++];
        bubbleSignal(k);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
    while(j<right)
    {

        data[k++]=Right[j++];
        bubbleSignal(k);
        QThread::msleep(static_cast<unsigned int>(mDelay));
    }
}
void Bubble::mergeSort(int L,int R)/*分解函数*/
{
    if(L==R)
        return;
    else
    {
        int M=(L+R)/2;
        mergeSort(L,M);    /*通过递归进行分解*/
        mergeSort(M+1,R);
        merge(L,M+1,R);
    }
}
