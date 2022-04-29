#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define TRUE 1
#define FALSE 0

//���濪ʼ�Զ�����������
typedef int vertextextype;
typedef int edgetype;
typedef int status;

//�ڽӱ�
typedef struct EdgeTable
{
    int vertextex; //��Ӧ������±�
    edgetype weight; //���ϵ�Ȩ�أ�����еĻ���
    struct EdgeTable *next; //ָ���붥����Ȼ������صĽ��
}EdgeTable;

typedef struct //����
{
    int in; //���
    vertextextype data;
    EdgeTable *nextedge;
}vertextex,vertextexTable[MAXSIZE];

typedef struct
{
    vertextexTable vertex; //����
    int numofvertextex,numofedge; //��������ͱ߸���
}AdjTable,*AdjTablePoint;

//�ڽӾ���
typedef struct
{
    vertextextype ver[MAXSIZE]; //��������
    edgetype edge[MAXSIZE][MAXSIZE]; //������
    int numofvertex,numofedge; //���������߸���
}Graph;


//����ͼ
void CreateMGraph(Graph *G)/* ����ͼ */
{
	int i, j;
	
	/* printf("����������Ͷ�����:"); */
	G->numofedge=MAXSIZE;
	G->numofvertex=MAXSIZE;

	for (i = 0; i < G->numofvertex; i++)/* ��ʼ��ͼ */
	{
		G->ver[i]=i;
	}

	for (i = 0; i < G->numofvertex; i++)/* ��ʼ��ͼ */
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


//�����ڽӾ��󹹽��ڽӱ�
void CreateALGraph(Graph G,AdjTablePoint *GL)
{
	int i,j;
	EdgeTable *e;

	*GL = (AdjTablePoint)malloc(sizeof(AdjTable));

	(*GL)->numofvertextex=G.numofvertex;
	(*GL)->numofedge=G.numofedge;
	for(i= 0;i <G.numofvertex;i++) /* ���붥����Ϣ����������� */
	{
		(*GL)->vertex[i].in=0;
		(*GL)->vertex[i].data=G.ver[i];
		(*GL)->vertex[i].nextedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(i=0;i<G.numofvertex;i++) /* �����߱� */
	{ 
		for(j=0;j<G.numofvertex;j++)
		{
			if (G.edge[i][j]==1)
			{
				e=(EdgeTable *)malloc(sizeof(EdgeTable));
				e->vertextex=j;					/* �ڽ����Ϊj  */                        
				e->next=(*GL)->vertex[i].nextedge;	/* ����ǰ�����ϵ�ָ��Ľ��ָ�븳ֵ��e */
				(*GL)->vertex[i].nextedge=e;		/* ����ǰ�����ָ��ָ��e  */  
				(*GL)->vertex[j].in++;
				
			}
		}
	}
	
}


//�����������޻�·������1����֮������0
status TopoSort(AdjTablePoint GL)
{
    EdgeTable *e;
    int i,j;
    int stacktop;
    int top=0; 
    int count=0; //����
    int *stack;

    stack=(int *)malloc(GL->numofvertextex * sizeof(int)); //���������ջ
    //�����Ϊ0�Ķ�����ջ
    for(i=0;i<GL->numofvertextex;i++)
    {
        if(0==GL->vertex[i].in)
        {
            stack[++top]=i;
        }
    }

    //��ջ�ڻ���Ԫ��ʱ
    while(top!=0)
    {
        stacktop=stack[top--];
        printf("%d-> ",GL->vertex[stacktop].data);
        count++;
        
        //����֮��صĶ�����������޸���ȣ����������Ϊ0�Ķ��㣬����ջ
        for(e=GL->vertex[stacktop].nextedge;e;e=e->next)
        {
            j=e->vertextex;
            if(!(--GL->vertex[j].in)) //�����Ϊ0
            {
                stack[++top]=j; //��ջ
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


//������main������֤
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