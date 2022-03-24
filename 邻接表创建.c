#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

//下面开始自定义类型名称
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
