#include <stdio.h>
#define MAXSIZE 10
#define INFINITY 65535

//下面开始自定义类型名字
typedef char vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //顶点数组
    edgetype edge[MAXSIZE][MAXSIZE]; //边数组
    int numofver,numofedge; //顶点个数与边个数
}Graph;

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