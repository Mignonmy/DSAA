#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define INFINITY 65535

//下面开始自定义类型名字
typedef int vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //顶点数组
    edgetype edge[MAXSIZE][MAXSIZE]; //边数组
    int numofver,numofedge; //顶点个数与边个数
}Graph;
typedef int fore_ver[MAXSIZE]; //前驱结点
typedef int shortpathweight[MAXSIZE]; //最短路径权值


//构建图
void CreateGraph(Graph *G)
{
	int i, j;

	//printf("请输入边数和顶点数:");
	G->numofedge=16;
	G->numofver=9;

	for (i = 0; i < G->numofver; i++)/* 初始化图 */
	{
		G->ver[i]=i;
	}

	for (i = 0; i < G->numofver; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numofver; j++)
		{
			if (i==j)
				G->edge[i][j]=0;
			else
				G->edge[i][j] = G->edge[j][i] =INFINITY;
		}
	}

	G->edge[0][1]=1;
	G->edge[0][2]=5; 
	G->edge[1][2]=3; 
	G->edge[1][3]=7; 
	G->edge[1][4]=5; 

	G->edge[2][4]=1; 
	G->edge[2][5]=7; 
	G->edge[3][4]=2; 
	G->edge[3][6]=3; 
	G->edge[4][5]=3;

	G->edge[4][6]=6;
	G->edge[4][7]=9; 
	G->edge[5][7]=5; 
	G->edge[6][7]=2; 
	G->edge[6][8]=7;

	G->edge[7][8]=4;


	for(i = 0; i < G->numofver; i++)
	{
		for(j = i; j < G->numofver; j++)
		{
			G->edge[j][i] =G->edge[i][j];
		}
	}
}

void ShortPath_Dijkstra(Graph G,int v,fore_ver *F,shortpathweight *S)
{
    int i,j;
    int min_weight; //最小权值
    int index;
    int judge[MAXSIZE]; //该数组数值为1时表示已求得从源顶点到该下标顶点最短路径
    
    //初始化，源顶点为v
    for(i=0;i<G.numofver;i++)
    {
        judge[i]=0; //全部顶点初始化为未知最短路径
        (*S)[i]=G.edge[v][i]; //记录与v有关联的顶点权值
        (*F)[i]=-1; //目前还未确定前驱结点
    }

    (*S)[v]=0; //v顶点至v顶点的路径为0
    judge[v]=1; //v顶点至v顶点不需要求最短路径

    //主循环开始
    for(i=1;i<G.numofver;i++){
        min_weight=INFINITY;

        for(j=0;j<G.numofver;j++){
            //比较得出下一个最小权值顶点
            if(!judge[j]&&(*S)[j]<min_weight)
            {
                index=j; //不断循环最后获取所求顶点
                min_weight=(*S)[j];
            }
        }

        judge[index]=1; //找到后设置为1
        
        //修正当前最短路径及权值
        for(j=0;j<G.numofver;j++)
        {
            //找到更短路径，修正F数组和S数组
            if(!judge[j]&&(min_weight+G.edge[index][j]<(*S)[j]))
            {
                (*S)[j]=min_weight+G.edge[index][j];
                (*F)[j]=index;
            }
        }
    }
}


//展示最短路径
void ShowPath(Graph G,int v,fore_ver F,shortpathweight S)
{
    int i,j;

    //最短路径
    printf("the reverse order of shortpath are as follow:\n");
    for(i=1;i<G.numofver;i++)
    {
        printf("v%d-v%d:",v,i);
        j=i;
        while(F[j]!=-1)
        {
            printf("%d ",F[j]);
            j=F[j];
        }
        printf("\n");
    }

    //源顶点到各顶点的最短权值
    printf("the each shortweight from sourse ver are as follow:\n");
    for(i=1;i<G.numofver;i++)
    {
        printf("v%d-v%d : %d\n",G.ver[0],G.ver[i],S[i]);
    }
}


//下面用main函数验证
int main()
{
    int v;
    Graph G;
    fore_ver F;
    shortpathweight S;
    v=0; //本次源顶点设置为0

    CreateGraph(&G);
    ShortPath_Dijkstra(G,v,&F,&S);
    ShowPath(G,v,F,S);

    return 0;
}