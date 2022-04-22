#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define INFINITY 65535

//���濪ʼ�Զ�����������
typedef int vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //��������
    edgetype edge[MAXSIZE][MAXSIZE]; //������
    int numofver,numofedge; //���������߸���
}Graph;
typedef int fore_ver[MAXSIZE][MAXSIZE]; //ǰ��������
typedef int shortpathweight[MAXSIZE][MAXSIZE]; //���·��Ȩֵ����


//����ͼ
void CreateGraph(Graph *G)
{
	int i, j;

	//printf("����������Ͷ�����:");
	G->numofedge=16;
	G->numofver=9;

	for (i = 0; i < G->numofver; i++)/* ��ʼ��ͼ */
	{
		G->ver[i]=i;
	}

	for (i = 0; i < G->numofver; i++)/* ��ʼ��ͼ */
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

    //���·��Ȩֵ������ǰ��������ĳ�ʼ��
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            (*S)[i][j]=G.edge[i][j]; //�ʼ���·��Ȩֵ���ڽӾ�����ͬ
            (*F)[i][j]=j;
        }
    }

    //��ѭ����ʼ
    for(index=0;index<G.numofver;index++){
        for(i=0;i<G.numofver;i++){
            for(j=0;j<G.numofver;j++){
                //�������·��Ȩֵ������ǰ��������
                if((*S)[i][j]>(*S)[i][index]+(*S)[index][j])
                {
                    (*S)[i][j]=(*S)[i][index]+(*S)[index][j];
                    (*F)[i][j]=(*F)[i][index];
                }
            }
        }
    }
}


//չʾ���·��
void ShowPath(Graph G,fore_ver F,shortpathweight S)
{
    int i,j,index;

    //���·����Ȩֵ
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

    //���·��Ȩֵ����
    printf("the shortpathweight array are as follow:\n");
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            printf("%d\t",S[i][j]);
        }
        printf("\n");
    }

    //ǰ��������
    printf("the fore_ver array are as follow:\n");
    for(i=0;i<G.numofver;i++){
        for(j=0;j<G.numofver;j++){
            printf("%d ",F[i][j]);
        }
        printf("\n");
    }
}


//������main������֤
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