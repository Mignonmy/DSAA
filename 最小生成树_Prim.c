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

//����һ��������ͼ���ڽӾ���
void CreateUDGraph(Graph *G)
{
    int i,j,k; //ѭ��������
    int weight; //Ȩ��
    vertextype v1,v2; //����1������2
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
        for(index1=0;index1<G->numofver;index1++){
            if(G->ver[index1]==v1){
                break;
            }
        }
        for(index2=0;index2<G->numofver;index2++){
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
        printf("\n");
    }
}

//��С�������㷨
void MiniSpanTree_Prim(Graph G)
{
    int min,i,j,min_index;
    int comparearray[MAXSIZE];
    int allrelatedvertex[MAXSIZE];

    comparearray[0]=0;
    allrelatedvertex[0]=0;

    //��ȡ���һ�������йص�Ȩֵ
    for(i=1;i<G.numofver;i++)
    {
        comparearray[i]=G.edge[0][i];
        allrelatedvertex[i]=0;
    }

    //����ÿ������
    for(i=1;i<G.numofver;i++)
    {
        min=INFINITY;
        j=1;
        min_index=0;

        //�Ƚ��й�Ȩֵ
        while(j<G.numofver)
        {
            if(comparearray[j]!=0&&comparearray[j]<min) //����δ��������Ȩֵ
            {
                min=comparearray[j]; //�õ�ǰȨֵ��Ϊ��Сֵ
                min_index=j; //��¼��ǰ��СȨֵ�±�
            }
            j++;
        }

        //��ӡ��ǰ������С���Ľ�չ��
        printf("(%d,%d)\n",allrelatedvertex[min_index],min_index); //allrelatedvertex[min_index]����һ��������
        comparearray[min_index]=0; //��ǰ������������

        //�ڵ�ǰ���ɵĲ�����С���Ļ����ϣ�������֮��صĶ����Ȩֵ
        for(j=1;j<G.numofver;j++)
        {
            if(comparearray[j]!=0&&G.edge[min_index][j]<comparearray[j])
            {
                comparearray[j]=G.edge[min_index][j];
                allrelatedvertex[j]=min_index;
            }
        }
    }
}


//������main������֤
int main()
{
    Graph G;
    CreateUDGraph(&G);
    ShowGraph(G);
    MiniSpanTree_Prim(G);

    return 0;
}