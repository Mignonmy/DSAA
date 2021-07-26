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
typedef struct link
{
    elemtype data;
    struct link * next;
}linkqueue;

typedef struct link * linkpoint;

typedef struct
{
    linkpoint front,rear;
}forlinkqueue;


//初始化队列
status InitQueue(forlinkqueue *Q)
{
    Q->front=Q->rear=(linkpoint)malloc(sizeof(linkqueue)); //申请结构内存
    if(!Q->front)
        exit(OVERFLOW); //系统内存溢出，强制终止程序

    Q->front->next=NULL;//讲头结点后继点设为空指针
    return OK;
}


//若队列存在，摧毁它
status DestroyQueue(forlinkqueue *Q)
{
    while(Q->front)
    {
        Q->rear=Q->front->next; //先让头结点的后继点
        free(Q->front); //释放头结点
        Q->front=Q->rear; //头指针指向下一个元素，后面不断更替，释放
    }
    return OK;
}


//清空队列
status ClearQueue(forlinkqueue *Q)
{
    linkpoint s,temp;
    Q->rear=Q->front; //让尾指针也指向头结点
    s=Q->front->next; //从第一个结点（非头结点）开始
    Q->front->next=NULL; //头结点的后继结点指向自己
    while(s)
    {
        temp=s; //让其替代第一个结点
        s=s->next; //移至下一个结点
        free(temp); //释放原本上一个结点
    }
    return OK;
}


//若队列为空，返回TRUE，否则返回FALSE
status QueueEmptyJudge(forlinkqueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}


//获取队列内元素个数
int QueueLen(forlinkqueue Q)
{
    int cnt=0;
    linkpoint p;
    p=Q.front;
    while(p!=Q.rear)
    { 
        p=p->next;  //当p为第一个结点时（非头结点），计数开始
        cnt++;
    }
    return cnt;
}


//若队列不空，用e返回队头元素
status GetHead(forlinkqueue Q,elemtype *e)
{
    if(Q.front==Q.rear) //队列空
        return ERROR;
    linkpoint p;
    p=Q.front->next; //让p指向第一个结点
    *e=p->data; //记录第一个结点的数据
    return OK;
}


//插入新元素e
status AddQueue(forlinkqueue *Q,elemtype e)
{
    linkpoint s=(linkpoint)malloc(sizeof(linkqueue)); //申请内存
    if(!s)
        exit(OVERFLOW);

    s->data=e; //为数据域赋值
    Q->rear->next=s; //让最后一个结点的后继结点是新申请的结点
    s->next=NULL; //为指针域赋予空指针
    Q->rear=s; //改变尾指针，让其指向新申请的结构
    return OK;
}


//若队列不空，删除Q的队头元素，用e放回其值
status OutQueue(forlinkqueue *Q,elemtype *e)
{
    if(Q->rear==Q->front)
        return ERROR;
    linkpoint p;
    p=Q->front->next; //从第一个结点（非头结点）开始
    *e=p->data; //记录要删除的结点的数据域的值
    Q->front->next=p->next; //让头指针的后继结点为要删除结点的后继结点
    if(Q->rear==p) //若此时第一个结点就是最后一个结点，删除之后就剩下头结点
        Q->rear=Q->front; //所以要让头指针与尾指针同时指向头结点
    free(p); //释放
    return OK;
}


//展示当前队列
void ShowQueue(forlinkqueue Q)
{
    printf("now show the queuq:");
    linkpoint p;
    p=Q.front->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}


//下面用main函数验证
int main(void)
{
    status dev;
    forlinkqueue Q;
    elemtype e;
    
    //创造一个空队列
    dev=InitQueue(&Q);
    if(dev)
        printf("creat queue sucessfully\n");
    printf("the len of this queue is %d\n",QueueLen(Q));

    //插入元素
    AddQueue(&Q,5);
    AddQueue(&Q,-5);
    AddQueue(&Q,10);
    printf("after that,the len of this queue is %d\n",QueueLen(Q));

    //空队列判断
    dev=QueueEmptyJudge(Q);
    if(!dev)
        printf("this queue is not void\n");
    ShowQueue(Q);

    //获取队列头元素
    dev=GetHead(Q,&e);
    if(dev==OK)
        printf("the head of this queue is %d\n",e);

    //删除队头元素,看新的队头元素
    OutQueue(&Q,&e);
    printf("after delte ");
    ShowQueue(Q);
    dev=GetHead(Q,&e);
    if(dev==OK)
        printf("the new head of this queue is %d\n",e);

    //清空与摧毁队列
    ClearQueue(&Q);
	printf("after clear,Q.front=%p Q.rear=%p Q.front->next=%p\n",Q.front,Q.rear,Q.front->next);
	DestroyQueue(&Q);
	printf("after destory,Q.front=%u Q.rear=%u\n",Q.front, Q.rear);
    return 0;
}
