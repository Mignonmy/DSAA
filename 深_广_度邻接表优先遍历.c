#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 9
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//���濪ʼ�Զ�����������
//�ȶ���ߣ���������ߣ����ı�������㣬���붥�������Ϣ
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

//����
typedef int elemtype;
typedef int status;
typedef struct link
{
    elemtype data;
    struct link * next;
}linkqueue;

typedef struct link * linkpoint;

typedef struct
{
    linkpoint front,rear;
}forlinkqueue;


//ȫ�ֱ���
int sign[MAXSIZE];

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

//�ڽӱ�������ȵݹ��㷨
void DFS(AdjTable G,int i)
{
    EdgeTable *p;
    sign[i]=1;
    printf("%c",G.ver[i].data);
    p=G.ver[i].nextedge;
    while(p)
    {
        if(!sign[p->index])
        {
            DFS(G,p->index);
            p=p->next;
        }
    }
}

//�ڽӱ���ȱ�������
void DFSTraverse(AdjTable G)
{
    for(int i=0;i<G.numofvertex;i++)
    {
        sign[i]=0;
    }
    for(int j=0;j<G.numofvertex;j++)
    {
        if(!sign[j])
        {
            DFS(G,j);
        }
    }
}

//��ʼ������
status InitQueue(forlinkqueue *Q)
{
    Q->front=Q->rear=(linkpoint)malloc(sizeof(linkqueue)); //����ṹ�ڴ�
    if(!Q->front)
        exit(OVERFLOW); //ϵͳ�ڴ������ǿ����ֹ����

    Q->front->next=NULL;//��ͷ����̵���Ϊ��ָ��
    return OK;
}

//������Ϊ�գ�����TRUE�����򷵻�FALSE
status QueueEmptyJudge(forlinkqueue Q)
{
    if(Q.front==Q.rear)
        return TRUE;
    else
        return FALSE;
}

//������Ԫ��e
status AddQueue(forlinkqueue *Q,elemtype e)
{
    linkpoint s=(linkpoint)malloc(sizeof(linkqueue)); //�����ڴ�
    if(!s)
        exit(OVERFLOW);

    s->data=e; //Ϊ������ֵ
    Q->rear->next=s; //�����һ�����ĺ�̽����������Ľ��
    s->next=NULL; //Ϊָ�������ָ��
    Q->rear=s; //�ı�βָ�룬����ָ��������Ľṹ
    return OK;
}


//�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e�Ż���ֵ
status OutQueue(forlinkqueue *Q,elemtype *e)
{
    if(Q->rear==Q->front)
        return ERROR;
    linkpoint p;
    p=Q->front->next; //�ӵ�һ����㣨��ͷ��㣩��ʼ
    *e=p->data; //��¼Ҫɾ���Ľ����������ֵ
    Q->front->next=p->next; //��ͷָ��ĺ�̽��ΪҪɾ�����ĺ�̽��
    if(Q->rear==p) //����ʱ��һ�����������һ����㣬ɾ��֮���ʣ��ͷ���
        Q->rear=Q->front; //����Ҫ��ͷָ����βָ��ͬʱָ��ͷ���
    free(p); //�ͷ�
    return OK;
}

//�ڽӱ������ȱ����㷨�����
void BFDTraverse(AdjTable G)
{
    EdgeTable *p;
    forlinkqueue Q;
    for(int i=0;i<G.numofvertex;i++)
    {
        sign[i]=0;
    }
    InitQueue(&Q);
    for(int i=0;i<G.numofvertex;i++)
    {
        if(!sign[i])
        {
            sign[i]=1;
            printf("%c",G.ver[i].data);
            AddQueue(&Q,i);
            while(!QueueEmptyJudge(Q))
            {
                OutQueue(&Q,&i);
                p=G.ver[i].nextedge;
                while(p)
                {
                    if(!sign[p->index])
                    {
                        sign[p->index]=1;
                        printf("%c",G.ver[i].data);
                        AddQueue(&Q,p->index);
                    }
                    p=p->next;
                }
            }
        }
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
