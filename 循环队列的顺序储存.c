#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名称
typedef int elemtype;
typedef int status;
typedef struct
{
    elemtype data[MAXSIZE];
    int front;
    int rear;
}queue;


//初始化一个空队列
status InitQueue(queue *Q)
{
    Q->front=0;
    Q->rear=0;
    return OK;
}


//清空队列
status ClearQueue(queue *Q)
{
    Q->rear=Q->front=0;
    return OK;
}


//是否为空队列，是返回TRUE，否则返回FALSE
status QueueEmptyJudge(queue Q)
{
    if(Q.front==Q.rear) //队空
        return TRUE;
    else
        return FALSE;
}


//获取队列元素个数
int QueueLen(queue Q)
{
    return (Q.rear+MAXSIZE-Q.front)%MAXSIZE; //这里取余保证下标在最大范围内
}


//获取队首元素，用e返回其值
status GetHead(queue Q,elemtype *e)
{
    if(Q.rear==Q.front)   //队列为空
        return ERROR;
    
    *e=Q.data[Q.front];
    return OK;
}


//若队列未满，插入新元素e
status AddQueue(queue *Q,elemtype e)
{
    if((Q->rear+1)%MAXSIZE==Q->front)
        return ERROR;
    Q->data[Q->rear]=e; //在队尾赋值进行插入
    Q->rear=(Q->rear+1)%MAXSIZE; //移动尾下标
    return OK;
}


//若队列不空，删除Q的队头元素，用e返回其值
status OutQueue(queue *Q,elemtype *e)
{
    if(Q->rear==Q->front) //队列空
        return ERROR;
    
    *e=Q->data[Q->front]; //记录队头元素
    Q->front=(Q->front+1)%MAXSIZE; //头下标移至下一位
    return OK;
}


//展示当前队内元素
void ShowQueue(queue Q)
{
    printf("now show the queue:");
    int j=Q.front;
    int i=0;
    while(j+i!=Q.rear)
    {
        printf("%d ",Q.data[j+i]);
        i=(i+1)%MAXSIZE;
    }
    printf("\n");
}


//下面用main函数验证
int main(void)
{
    queue Q;
    int num;
    int j=0;
    status dev;
    elemtype e;

    //初始化队列
    InitQueue(&Q);
    
    //插入100-118
    do{
        num=j+100;
        j++;
        AddQueue(&Q,num);
    }while(j<MAXSIZE-1);

    ShowQueue(Q);
    printf("now the len of this queue is %d\n",QueueLen(Q));
    GetHead(Q,&e);
    printf("the head elem of this queue is %d\n",e);

    
    //删除队首元素100
    OutQueue(&Q,&e);
    // printf("%d %d\n",Q.front,Q.rear);
    ShowQueue(Q);

}
