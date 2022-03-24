#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 9
#define INFINITY 65535
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名字
//图
typedef char vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //顶点数组
    edgetype edge[MAXSIZE][MAXSIZE]; //边数组
    int numofver,numofedge; //顶点个数与边个数
}Graph;

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

//创建一个无向网图的邻接矩阵
void CreateUDGraph(Graph *G)
{
    int i,j,k; //循环计数用
    int weight; //权重
    int v1,v2; //顶点1，顶点2
    printf("please enter the numofver,numofedge:\n");
    scanf("%d,%d",&G->numofver,&G->numofedge); //获取顶点数和边数

    //初始化矩阵，把对角线的值设为0，其他设为∞
    for(i=0;i<G->numofver;i++){
        for(j=0;j<G->numofver;j++){
            if(i==j){
                G->edge[i][j]=0;
            }
            else{
                G->edge[i][j]=INFINITY;
            }
        }
    }

    //将顶点信息依次进行数组
    for(i=0;i<G->numofver;i++){
        printf("please enter the %dth vertex:\n",i+1);
        scanf("%d",&G->ver[i]);
    }
    printf("\n");

    //获取边的信息
    for(k=0;k<G->numofedge;k++){
        int index1,index2;
        printf("please enter the information of two vertex and edge(ver,ver,edge):\n");
        scanf("%d,%d,%d",&v1,&v2,&weight);

        //搜索顶点对应的数组下标
        for(index1=0;i<G->numofver;i++){
            if(G->ver[index1]==v1){
                break;
            }
        }
        for(index2=0;i<G->numofver;i++){
            if(G->ver[index2]==v2){
                break;
            }
        }

        G->edge[index1][index2]=weight;
        G->edge[index2][index1]=G->edge[index1][index2]; //无向图，矩阵对称
        
    }
}

//邻接矩阵深度优先遍历递归算法
void DFS(Graph G,int i)
{
    sign[i]=0;
    printf("%c",G.ver[i]);
    for(int j=0;j<G.numofver;j++)
    {
        if(G.edge[i][j]==1&&!sign[i])
        {
            DFS(G,j); //对未访问的邻接顶点递归调用
        }
    }
}

//邻接矩阵的深度遍历操作
void DFSTraverse(Graph G)
{
    //初始化所有顶点，将所有顶点设置为未访问
    for(int i=0;i<G.numofver;i++)
    {
        sign[i]=0;
    }
    for(int j=0;j<G.numofver;j++)
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

//邻接矩阵广度遍历算法与操作
void BFSTraverse(Graph G)
{
    forlinkqueue Q;
    //初始化顶点
    for(int i=0;i<G.numofver;i++)
    {
        sign[i]=0;
    }
    InitQueue(&Q);
    for(int i=0;i<G.numofver;i++)
    {
        if(!sign[i])
        {
            sign[i]=1; //进入后设置顶点为已访问
            printf("%c",G.ver[i]);
            AddQueue(&Q,i);
            while(!QueueEmptyJudge)
            {
                OutQueue(&Q,&i);
                for(int j=0;j<G.numofver;j++)
                {
                    if(G.edge[i][j]==1&&!sign[j]) //判断其他顶点，若当前结点存在且边未访问过
                    {
                        sign[j]=1;
                        printf("%c",G.ver[j]);
                        AddQueue(&Q,j);
                    }
                }
            }
        }
    }
}

//展示当前无向权重图
void ShowGraph(Graph G)
{
    printf("the result are as follow:\n");
    printf("\t");
    for(int i=0;i<G.numofver;i++){
        printf("%6d",G.ver[i]); //行显示顶点
    }

    for(int i=0;i<G.numofver;i++){
        printf("\n%8d",G.ver[i]); //逐列显示顶点
        for(int j=0;j<G.numofver;j++){
            if(G.edge[i][j]==INFINITY){
                printf("%6s","∞");
            }
            else{
                printf("%6d",G.edge[i][j]);
            }
        }
    }
}

//下面用main验证
int main()
{
    Graph G;
    CreateUDGraph(&G);
    ShowGraph(G);

    return 0;
}