#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 9
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名称
//先定义边，顶点包含边，最后的表包含顶点，边与顶点个数信息
typedef int vertextype;
typedef int edgetype;
typedef struct EdgeTable
{
    int index; //对应顶点的下标
    edgetype weight; //边上的权重（如果有的话）
    struct EdgeTable *next; //指向与顶点出度或入度相关的结点
}EdgeTable;

typedef struct //顶点
{
    vertextype data;
    EdgeTable *nextedge;
}Vertex,VertexTable[MAXSIZE];

typedef struct
{
    VertexTable ver; //顶点
    int numofvertex,numofedge; //顶点个数和边个数
}AdjTable;

//队列
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


//全局变量
int sign[MAXSIZE];

//创建一个无向图邻接表
void CreateGraphTable(AdjTable *G)
{
    int i,j,k;
    EdgeTable *e; //指向边表的指针
    printf("please enter the numofvertex,numofedge:\n");
    scanf("%d,%d",&G->numofvertex,&G->numofedge);
    
    //获取顶点的信息
    for(i=0;i<G->numofvertex;i++)
    {
        printf("please enter the data of vertex:\n");
        scanf("%d",&G->ver[i].data);
        G->ver[i].nextedge=NULL; //将顶点的指向为空，此时只有顶点表，没有边表
    }

    //建立边表，头插法插入边表
    for(k=0;k<G->numofedge;k++)
    {
        printf("please enter a pair of vertex:\n");
        scanf("%d %d",&i,&j);
        
        e=(EdgeTable*)malloc(sizeof(EdgeTable)); //申请边结点
        e->index=j;
        e->next=G->ver[i].nextedge;
        G->ver[i].nextedge=e;
        e=(EdgeTable*)malloc(sizeof(EdgeTable)); //因为是无向图，双向申请
        e->index=i;
        e->next=G->ver[j].nextedge;
        G->ver[j].nextedge=e;
    }
}

//邻接表深度优先递归算法
void DFS(AdjTable G,int i)
{
    EdgeTable *p;
    sign[i]=1;
    printf("%c",G.ver[i].data);
    p=G.ver[i].nextedge;
    while(p)
    {
        if(!sign[p->index])
        {
            DFS(G,p->index);
            p=p->next;
        }
    }
}

//邻接表深度遍历操作
void DFSTraverse(AdjTable G)
{
    for(int i=0;i<G.numofvertex;i++)
    {
        sign[i]=0;
    }
    for(int j=0;j<G.numofvertex;j++)
    {
        if(!sign[j])
        {
            DFS(G,j);
        }
    }
}

//初始化队列
status InitQueue(forlinkqueue *Q)
{
    Q->front=Q->rear=(linkpoint)malloc(sizeof(linkqueue)); //申请结构内存
    if(!Q->front)
        exit(OVERFLOW); //系统内存溢出，强制终止程序

    Q->front->next=NULL;//讲头结点后继点设为空指针
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

//邻接表广度优先遍历算法与操作
void BFDTraverse(AdjTable G)
{
    EdgeTable *p;
    forlinkqueue Q;
    for(int i=0;i<G.numofvertex;i++)
    {
        sign[i]=0;
    }
    InitQueue(&Q);
    for(int i=0;i<G.numofvertex;i++)
    {
        if(!sign[i])
        {
            sign[i]=1;
            printf("%c",G.ver[i].data);
            AddQueue(&Q,i);
            while(!QueueEmptyJudge(Q))
            {
                OutQueue(&Q,&i);
                p=G.ver[i].nextedge;
                while(p)
                {
                    if(!sign[p->index])
                    {
                        sign[p->index]=1;
                        printf("%c",G.ver[i].data);
                        AddQueue(&Q,p->index);
                    }
                    p=p->next;
                }
            }
        }
    }
}



//展示当前邻接表
void ShowTable()
{
    printf("now show the table:\n");
    //待完成
}

//下面用main函数验证
int main()
{
    AdjTable G;
    CreateGraphTable(&G);

    return 0;
}
