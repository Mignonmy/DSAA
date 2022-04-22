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
typedef int fore_ver[MAXSIZE]; //ǰ�����
typedef int shortpathweight[MAXSIZE]; //���·��Ȩֵ


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

void ShortPath_Dijkstra(Graph G,int v,fore_ver *F,shortpathweight *S)
{
    int i,j;
    int min_weight; //��СȨֵ
    int index;
    int judge[MAXSIZE]; //��������ֵΪ1ʱ��ʾ����ô�Դ���㵽���±궥�����·��
    
    //��ʼ����Դ����Ϊv
    for(i=0;i<G.numofver;i++)
    {
        judge[i]=0; //ȫ�������ʼ��Ϊδ֪���·��
        (*S)[i]=G.edge[v][i]; //��¼��v�й����Ķ���Ȩֵ
        (*F)[i]=-1; //Ŀǰ��δȷ��ǰ�����
    }

    (*S)[v]=0; //v������v�����·��Ϊ0
    judge[v]=1; //v������v���㲻��Ҫ�����·��

    //��ѭ����ʼ
    for(i=1;i<G.numofver;i++){
        min_weight=INFINITY;

        for(j=0;j<G.numofver;j++){
            //�Ƚϵó���һ����СȨֵ����
            if(!judge[j]&&(*S)[j]<min_weight)
            {
                index=j; //����ѭ������ȡ���󶥵�
                min_weight=(*S)[j];
            }
        }

        judge[index]=1; //�ҵ�������Ϊ1
        
        //������ǰ���·����Ȩֵ
        for(j=0;j<G.numofver;j++)
        {
            //�ҵ�����·��������F�����S����
            if(!judge[j]&&(min_weight+G.edge[index][j]<(*S)[j]))
            {
                (*S)[j]=min_weight+G.edge[index][j];
                (*F)[j]=index;
            }
        }
    }
}


//չʾ���·��
void ShowPath(Graph G,int v,fore_ver F,shortpathweight S)
{
    int i,j;

    //���·��
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

    //Դ���㵽����������Ȩֵ
    printf("the each shortweight from sourse ver are as follow:\n");
    for(i=1;i<G.numofver;i++)
    {
        printf("v%d-v%d : %d\n",G.ver[0],G.ver[i],S[i]);
    }
}


//������main������֤
int main()
{
    int v;
    Graph G;
    fore_ver F;
    shortpathweight S;
    v=0; //����Դ��������Ϊ0

    CreateGraph(&G);
    ShortPath_Dijkstra(G,v,&F,&S);
    ShowPath(G,v,F,S);

    return 0;
}