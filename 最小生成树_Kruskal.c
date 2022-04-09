#include <stdio.h>
#include <stdlib.h>
#define INFINITY 65535
#define MAXSIZE 20

//���濪ʼ�Զ�����������
typedef int vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //��������
    edgetype edge[MAXSIZE][MAXSIZE]; //������
    int numofver,numofedge; //���������߸���
}Graph;
typedef struct
{
    int begin;
    int end;
    int weight;
}EdgeArray; //�߼�����

//����ͼ
void CreateGraph(Graph *G)
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numofedge=15;
	G->numofver=9;

	for (i = 0; i < G->numofver; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < G->numofver; j++)
		{
			if (i==j)
				G->edge[i][j]=0;
			else
				G->edge[i][j] = G->edge[j][i] = INFINITY;
		}
	}

	G->edge[0][1]=10;
	G->edge[0][5]=11; 
	G->edge[1][2]=18; 
	G->edge[1][8]=12; 
	G->edge[1][6]=16; 
	G->edge[2][8]=8; 
	G->edge[2][3]=22; 
	G->edge[3][8]=21; 
	G->edge[3][6]=24; 
	G->edge[3][7]=16;
	G->edge[3][4]=20;
	G->edge[4][7]=7; 
	G->edge[4][5]=26; 
	G->edge[5][6]=17; 
	G->edge[6][7]=19; 

	for(i = 0; i < G->numofver; i++)
	{
		for(j = i; j < G->numofver; j++)
		{
			G->edge[j][i] =G->edge[i][j];
		}
	}
}

//�߼�����Ľ�����������������ʹ��
void Swap(EdgeArray *e,int i, int j)
{
	int temp;
	temp = e[i].begin;
	e[i].begin = e[j].begin;
	e[j].begin = temp;
	temp = e[i].end;
	e[i].end = e[j].end;
	e[j].end = temp;
	temp = e[i].weight;
	e[i].weight = e[j].weight;
	e[j].weight = temp;
}

//�߼������Ȩֵ������
void sort(EdgeArray e[],Graph *G)
{
	int i, j;
	for ( i = 0; i < G->numofedge; i++)
	{
		for ( j = i + 1; j < G->numofedge; j++)
		{
			if (e[i].weight > e[j].weight)
			{
				Swap(e, i, j);
			}
		}
	}
	printf("after sort,the result are as follows:\n");
	for (i = 0; i < G->numofedge; i++)
	{
		printf("(%d, %d) %d\n", e[i].begin, e[i].end, e[i].weight);
	}

}


//��С�������㷨
void MiniSpanTree_Kruskal(Graph G)
{
    int i,j,ver1,ver2;
    int index=0; //���ڱ߼�����Ĺ�������
    EdgeArray e[MAXSIZE];
    int LoopJudge[MAXSIZE];

    //�߼�����Ĺ���
    for(i=0;i<G.numofver-1;i++){
        for(j=i+1;j<G.numofver;j++){
            if(G.edge[i][j]<INFINITY)
            {
                e[index].begin=i;
                e[index].end=j;
                e[index].weight=G.edge[i][j];
                index++;
            }
        }
    }

    //Ȩֵ����
    sort(e,&G);

    //LoopJudge�����ʼ��Ϊ0
    for(i=0;i<G.numofver;i++){
        LoopJudge[i]=0;
    }

    //���Ϲ���Ȩֵ��С�ı�ͬʱ�ж��Ƿ��γɻ�·
    for(i=0;i<G.numofedge;i++){
        ver1=IndexGive(LoopJudge,e[i].begin);
        ver2=IndexGive(LoopJudge,e[i].end);

        //�������㣨��������ֵ������ȣ�˵���˱�û���������������γɻ�·
        if(ver1!=ver2)
        {
            LoopJudge[ver1]=ver2;
            printf("(%d,%d) %d\n",e[i].begin,e[i].end,e[i].weight);
        }
    }
}


//�ж��Ƿ��л�·��Ҫ�������������
int IndexGive(int *LoopJudge,int index)
{
    while(LoopJudge[index]>0)
    {
        index=LoopJudge[index];
    }
    return index;
}


//������main������֤
int main(void)
{
	Graph G;
	CreateGraph(&G);
	MiniSpanTree_Kruskal(G);
	return 0;
}