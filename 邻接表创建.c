#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

//���濪ʼ�Զ�����������
typedef int vertextype;
typedef int edgetype;
typedef struct EdgeTable
{
    int index; //��Ӧ������±�
    edgetype weight; //���ϵ�Ȩ�أ�����еĻ���
    struct EdgeTable *next; //ָ���붥����Ȼ������صĽ��
}EdgeTable;

typedef struct //����
{
    vertextype data;
    EdgeTable *nextedge;
}Vertex,VertexTable[MAXSIZE];

typedef struct
{
    VertexTable ver; //����
    int numofvertex,numofedge; //��������ͱ߸���
}AdjTable;

//����һ������ͼ�ڽӱ�
void CreateGraphTable(AdjTable *G)
{
    int i,j,k;
    EdgeTable *e; //ָ��߱��ָ��
    printf("please enter the numofvertex,numofedge:\n");
    scanf("%d,%d",&G->numofvertex,&G->numofedge);
    
    //��ȡ�������Ϣ
    for(i=0;i<G->numofvertex;i++)
    {
        printf("please enter the data of vertex:\n");
        scanf("%d",&G->ver[i].data);
        G->ver[i].nextedge=NULL; //�������ָ��Ϊ�գ���ʱֻ�ж����û�б߱�
    }

    //�����߱�ͷ�巨����߱�
    for(k=0;k<G->numofedge;k++)
    {
        printf("please enter a pair of vertex:\n");
        scanf("%d %d",&i,&j);
        
        e=(EdgeTable*)malloc(sizeof(EdgeTable)); //����߽��
        e->index=j;
        e->next=G->ver[i].nextedge;
        G->ver[i].nextedge=e;
        e=(EdgeTable*)malloc(sizeof(EdgeTable)); //��Ϊ������ͼ��˫������
        e->index=i;
        e->next=G->ver[j].nextedge;
        G->ver[j].nextedge=e;
    }
}

//չʾ��ǰ�ڽӱ�
void ShowTable()
{
    printf("now show the table:\n");
    //�����
}

//������main������֤
int main()
{
    AdjTable G;
    CreateGraphTable(&G);

    return 0;
}
