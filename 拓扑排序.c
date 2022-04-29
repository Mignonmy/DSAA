#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名称
typedef int vertextextype;
typedef int edgetype;
typedef int status;

//邻接表
typedef struct EdgeTable
{
    int vertextex; //对应顶点的下标
    edgetype weight; //边上的权重（如果有的话）
    struct EdgeTable *next; //指向与顶点出度或入度相关的结点
}EdgeTable;

typedef struct //顶点
{
    int in; //入度
    vertextextype data;
    EdgeTable *nextedge;
}vertextex,vertextexTable[MAXSIZE];

typedef struct
{
    vertextexTable vertex; //顶点
    int numofvertextex,numofedge; //顶点个数和边个数
}AdjTable,*AdjTablePoint;

//邻接矩阵
typedef struct
{
    vertextextype ver[MAXSIZE]; //顶点数组
    edgetype edge[MAXSIZE][MAXSIZE]; //边数组
    int numofvertex,numofedge; //顶点个数与边个数
}Graph;


//构建图
void CreateMGraph(Graph *G)/* 构件图 */
{
	int i, j;
	
	/* printf("请输入边数和顶点数:"); */
	G->numofedge=MAXSIZE;
	G->numofvertex=MAXSIZE;

	for (i = 0; i < G->numofvertex; i++)/* 初始化图 */
	{
		G->ver[i]=i;
	}

	for (i = 0; i < G->numofvertex; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numofvertex; j++)
		{
			G->edge[i][j]=0;
		}
	}

	G->edge[0][4]=1;
	G->edge[0][5]=1; 
	G->edge[0][11]=1; 
	G->edge[1][2]=1; 
	G->edge[1][4]=1; 
	G->edge[1][8]=1; 
	G->edge[2][5]=1; 
	G->edge[2][6]=1;
	G->edge[2][9]=1;
	G->edge[3][2]=1; 
	G->edge[3][13]=1;
	G->edge[4][7]=1;
	G->edge[5][8]=1;
	G->edge[5][12]=1; 
	G->edge[6][5]=1; 
	G->edge[8][7]=1;
	G->edge[9][10]=1;
	G->edge[9][11]=1;
	G->edge[10][13]=1;
	G->edge[12][9]=1;
}


//利用邻接矩阵构建邻接表
void CreateALGraph(Graph G,AdjTablePoint *GL)
{
	int i,j;
	EdgeTable *e;

	*GL = (AdjTablePoint)malloc(sizeof(AdjTable));

	(*GL)->numofvertextex=G.numofvertex;
	(*GL)->numofedge=G.numofedge;
	for(i= 0;i <G.numofvertex;i++) /* 读入顶点信息，建立顶点表 */
	{
		(*GL)->vertex[i].in=0;
		(*GL)->vertex[i].data=G.ver[i];
		(*GL)->vertex[i].nextedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(i=0;i<G.numofvertex;i++) /* 建立边表 */
	{ 
		for(j=0;j<G.numofvertex;j++)
		{
			if (G.edge[i][j]==1)
			{
				e=(EdgeTable *)malloc(sizeof(EdgeTable));
				e->vertextex=j;					/* 邻接序号为j  */                        
				e->next=(*GL)->vertex[i].nextedge;	/* 将当前顶点上的指向的结点指针赋值给e */
				(*GL)->vertex[i].nextedge=e;		/* 将当前顶点的指针指向e  */  
				(*GL)->vertex[j].in++;
				
			}
		}
	}
	
}


//拓扑排序，若无回路，返回1，反之，返回0
status TopoSort(AdjTablePoint GL)
{
    EdgeTable *e;
    int i,j;
    int stacktop;
    int top=0; 
    int count=0; //计数
    int *stack;

    stack=(int *)malloc(GL->numofvertextex * sizeof(int)); //建立顶点个栈
    //将入度为0的顶点入栈
    for(i=0;i<GL->numofvertextex;i++)
    {
        if(0==GL->vertex[i].in)
        {
            stack[++top]=i;
        }
    }

    //当栈内还有元素时
    while(top!=0)
    {
        stacktop=stack[top--];
        printf("%d-> ",GL->vertex[stacktop].data);
        count++;
        
        //对与之相关的顶点遍历，并修改入度，若出现入度为0的顶点，则入栈
        for(e=GL->vertex[stacktop].nextedge;e;e=e->next)
        {
            j=e->vertextex;
            if(!(--GL->vertex[j].in)) //若入度为0
            {
                stack[++top]=j; //入栈
            }
        }
    }
    printf("\n");

    if(count<GL->numofvertextex)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


//下面用main函数验证
int main()
{
    Graph G;
    AdjTablePoint GL;
    int result;
    CreateMGraph(&G);
    CreateALGraph(G,&GL);

    result=TopoSort(GL);
    if(result==TRUE)
    {
        printf("succeed!");
    }

    return 0;
}