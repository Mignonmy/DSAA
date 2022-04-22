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
typedef int fore_ver[MAXSIZE][MAXSIZE]; //前驱结点矩阵
typedef int shortpathweight[MAXSIZE][MAXSIZE]; //最短路径权值矩阵


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


void ShortPath_Floyd(Graph G,fore_ver *F,shortpathweight *S)
{
    int i,j;
    int index;

    //最短路径权值矩阵与前驱结点矩阵的初始化
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            (*S)[i][j]=G.edge[i][j]; //最开始最短路径权值与邻接矩阵相同
            (*F)[i][j]=j;
        }
    }

    //主循环开始
    for(index=0;index<G.numofver;index++){
        for(i=0;i<G.numofver;i++){
            for(j=0;j<G.numofver;j++){
                //修正最短路径权值矩阵与前驱结点矩阵
                if((*S)[i][j]>(*S)[i][index]+(*S)[index][j])
                {
                    (*S)[i][j]=(*S)[i][index]+(*S)[index][j];
                    (*F)[i][j]=(*F)[i][index];
                }
            }
        }
    }
}


//展示最短路径
void ShowPath(Graph G,fore_ver F,shortpathweight S)
{
    int i,j,index;

    //最短路径及权值
    printf("the shortest path of each ver to each ver and his weight are as follow:\n");
    for(i=0;i<G.numofver;i++){
        for(j=i+1;j<G.numofver;j++){
            printf("v%d-v%d (weight: %d) ",i,j,S[i][j]);
            index=F[i][j];
            printf("path:%d",i);
            while(index!=j)
            {
                printf("->%d",index);
                index=F[index][j];
            }
            printf("->%d\n",j);
        }
        printf("\n");
    }

    //最短路径权值矩阵
    printf("the shortpathweight array are as follow:\n");
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            printf("%d\t",S[i][j]);
        }
        printf("\n");
    }

    //前驱结点矩阵
    printf("the fore_ver array are as follow:\n");
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            printf("%d ",F[i][j]);
        }
        printf("\n");
    }
}


//下面用main函数验证
int main()
{
    Graph G;
    fore_ver F;
    shortpathweight S;
    
    CreateGraph(&G);
    ShortPath_Floyd(G,&F,&S);
    ShowPath(G,F,S);

    return 0;
}