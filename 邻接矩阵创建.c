#include <stdio.h>
#define MAXSIZE 10
#define INFINITY 65535

//���濪ʼ�Զ�����������
typedef char vertextype;
typedef int edgetype;
typedef struct
{
    vertextype ver[MAXSIZE]; //��������
    edgetype edge[MAXSIZE][MAXSIZE]; //������
    int numofver,numofedge; //���������߸���
}Graph;

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