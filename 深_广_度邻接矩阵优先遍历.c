#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 9
#define INFINITY 65535
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//���濪ʼ�Զ�����������
//ͼ
typedef char vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //��������
    edgetype edge[MAXSIZE][MAXSIZE]; //������
    int numofver,numofedge; //���������߸���
}Graph;

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

//����һ��������ͼ���ڽӾ���
void CreateUDGraph(Graph *G)
{
    int i,j,k; //ѭ��������
    int weight; //Ȩ��
    int v1,v2; //����1������2
    printf("please enter the numofver,numofedge:\n");
    scanf("%d,%d",&G->numofver,&G->numofedge); //��ȡ�������ͱ���

    //��ʼ�����󣬰ѶԽ��ߵ�ֵ��Ϊ0��������Ϊ��
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

    //��������Ϣ���ν�������
    for(i=0;i<G->numofver;i++){
        printf("please enter the %dth vertex:\n",i+1);
        scanf("%d",&G->ver[i]);
    }
    printf("\n");

    //��ȡ�ߵ���Ϣ
    for(k=0;k<G->numofedge;k++){
        int index1,index2;
        printf("please enter the information of two vertex and edge(ver,ver,edge):\n");
        scanf("%d,%d,%d",&v1,&v2,&weight);

        //���������Ӧ�������±�
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
        G->edge[index2][index1]=G->edge[index1][index2]; //����ͼ������Գ�
        
    }
}

//�ڽӾ���������ȱ����ݹ��㷨
void DFS(Graph G,int i)
{
    sign[i]=0;
    printf("%c",G.ver[i]);
    for(int j=0;j<G.numofver;j++)
    {
        if(G.edge[i][j]==1&&!sign[i])
        {
            DFS(G,j); //��δ���ʵ��ڽӶ���ݹ����
        }
    }
}

//�ڽӾ������ȱ�������
void DFSTraverse(Graph G)
{
    //��ʼ�����ж��㣬�����ж�������Ϊδ����
    for(int i=0;i<G.numofver;i++)
    {
        sign[i]=0;
    }
    for(int j=0;j<G.numofver;j++)
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

//�ڽӾ����ȱ����㷨�����
void BFSTraverse(Graph G)
{
    forlinkqueue Q;
    //��ʼ������
    for(int i=0;i<G.numofver;i++)
    {
        sign[i]=0;
    }
    InitQueue(&Q);
    for(int i=0;i<G.numofver;i++)
    {
        if(!sign[i])
        {
            sign[i]=1; //��������ö���Ϊ�ѷ���
            printf("%c",G.ver[i]);
            AddQueue(&Q,i);
            while(!QueueEmptyJudge)
            {
                OutQueue(&Q,&i);
                for(int j=0;j<G.numofver;j++)
                {
                    if(G.edge[i][j]==1&&!sign[j]) //�ж��������㣬����ǰ�������ұ�δ���ʹ�
                    {
                        sign[j]=1;
                        printf("%c",G.ver[j]);
                        AddQueue(&Q,j);
                    }
                }
            }
        }
    }
}

//չʾ��ǰ����Ȩ��ͼ
void ShowGraph(Graph G)
{
    printf("the result are as follow:\n");
    printf("\t");
    for(int i=0;i<G.numofver;i++){
        printf("%6d",G.ver[i]); //����ʾ����
    }

    for(int i=0;i<G.numofver;i++){
        printf("\n%8d",G.ver[i]); //������ʾ����
        for(int j=0;j<G.numofver;j++){
            if(G.edge[i][j]==INFINITY){
                printf("%6s","��");
            }
            else{
                printf("%6d",G.edge[i][j]);
            }
        }
    }
}

//������main��֤
int main()
{
    Graph G;
    CreateUDGraph(&G);
    ShowGraph(G);

    return 0;
}