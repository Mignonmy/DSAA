#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define zero 0

//下面开始自定义类型
typedef int status;
typedef int elemtype;
typedef int bitree[MAXSIZE];
typedef struct 
{
    int level,order; //层数，层中的顺序
}position;


//初始化二叉树
status InitBitree(bitree T)
{
    int i;
    for(i=0;i<MAXSIZE;i++){
        T[i]=zero; //全部设置为0
    }
    return OK;
}
#define ClearBitree InitBitree //二叉树顺序储存中，两函数一样


//创造二叉树（此处数值为1-10）、
status CreatBitree(bitree T)
{
    int i=0;
    while(i<10)
    {
        T[i]=i+1;
        if(i!=0&&T[(i+1)/2-1]==zero&&T[i]!=zero) //出现无双亲且非根结点，第三个条件保证不是后面没用上的结点
        {
            printf("this node is not root and without parent\n");
            exit(ERROR);
        }
        i++; //若无异常，赋值继续
    }
    while(i<MAXSIZE) //让后面没用上的结点赋值为0;
    {
        T[i]=zero; 
        i++;  
    }
    return OK;
}


//空树返回TRUE，否则返回FALSE
status BitreeEmptyJudge(bitree T)
{
    if(T[0]==zero)
        return TRUE;
    else
        return FALSE;
}


//获得树T的深度
int BitreeDepth(bitree T)
{
    int i;
    int dep=-1;
    for(i=MAXSIZE-1;i>=0;i--){ //从后往前寻找树的最后一个结点
        if(T[i]!=zero) break;
    }
    i++; //这里的i是数组下标，+1才是第几个结点

    do
    {
        dep++;           
    }while(i>=pow(2,dep)); //反向利用性质：具有n个结点的完全二叉树的深度为[log2 n +1]

    return dep;
}


//用e返回树T的根值
status GetRoot(bitree T,elemtype *e)
{
    if(BitreeEmptyJudge(T))
    {
        return ERROR;
    }
    else
    {
        *e=T[0];
        return OK;
    }
}


//根据位置获取其值
elemtype GetE(bitree T,position e)
{
    return T[(int)pow(2,e.level-1)+e.order-2]; //用pow到达该层，用order到达该点，
                                               //减的2是在两者退一位适应数组从0开始的性质
}


//根据位置赋值
status Assign(bitree T,position p,elemtype value)
{
    int num=(int)pow(2,p.level-1)+p.order-2; //获取该位置在数组的下标
    if(value!=zero&&T[(num+1)/2-1]==zero) //给叶子赋非空值但双亲结点为空
        return ERROR;
    
    else if(value==zero&&(T[num*2+1]!=zero||T[num*2+1]!=zero)) //给双亲结点赋空值但叶子结点非空
        return ERROR;
    
    T[num]=value;
    return OK;
    
}


//获取非根节点e的双亲结点
elemtype GetParent(bitree T,elemtype e)
{
    int index;
    if(T[0]==zero)
        return zero;
    for(index=1;index<MAXSIZE;index++){ //遍历找到该结点
        if(T[index]==e)
            return T[(index+1)/2-1]; //返回该结点双亲值
    }
    return zero; //否则返回空值
}


//返回e的左孩子，若无，返回空值
elemtype GetLeChild(bitree T,elemtype e)
{
    int index;
    if(T[0]==zero)
        return zero;
    for(index=0;index<MAXSIZE;index++){ //遍历找到该结点
        if(T[index]==e)
            return T[(index*2+1)]; //返回该结点左孩子
    }
    return zero; //否则返回空值
}


//返回e的右孩子，若无，返回空值
elemtype GetRiChild(bitree T,elemtype e)
{
    int index;
    if(T[0]==zero)
        return zero;
    for(index=0;index<MAXSIZE;index++){ //遍历找到该结点
        if(T[index]==e)
            return T[(index*2+2)]; //返回该结点右孩子
    }
    return zero; //否则返回空值
}


//返回e的左兄弟，若无，返回空值
elemtype GetLeSibling(bitree T,elemtype e)
{
    int index;
    if(T[0]==zero)
        return ERROR;
    for(index=1;index<MAXSIZE;index++){ //遍历找到该结点
        if(T[index]==e&&index%2==0) //既然找左兄弟，该值处于右兄弟，右兄弟下标为偶数
            return T[index-1]; //返回该结点左兄弟
    }
    return zero; //否则返回空值
}


//返回e的右兄弟，若无，返回空值
elemtype GetRiSibling(bitree T,elemtype e)
{
    int index;
    if(T[0]==zero)
        return ERROR;
    for(index=1;index<MAXSIZE;index++){ //遍历找到该结点
        if(T[index]==e&&index%2) //既然找左兄弟，该值处于右兄弟，右兄弟下标为偶数
            return T[index+1]; //返回该结点左兄弟
    }
    return zero; //否则返回空值
}


//从num开始前序遍历二叉树
status PreOrderTraverse(bitree T,int num)
{
    if(T[0]==zero) //空树
        return ERROR;

    printf("%d ",T[num]);
    if(T[2*num+1]!=zero) //左子树不空
        PreOrderTraverse(T,2*num+1);
    if(T[2*num+2]!=zero) //右子树不空
        PreOrderTraverse(T,2*num+2);
}


//从num开始中序遍历二叉树
status InOrderTraverse(bitree T,int num)
{
    if(T[0]==zero) //空树
        return ERROR;
    
    if(T[2*num+1]!=zero)
        InOrderTraverse(T,2*num+1);
    printf("%d ",T[num]);

    if(T[2*num+2]!=zero)
        InOrderTraverse(T,2*num+2);
    
}


//从num开始后序遍历二叉树
status PostOrderTraverse(bitree T,int num)
{
    if(T[num]==zero) //空树
        return ERROR;

    if(T[2*num+1]!=zero)
        PostOrderTraverse(T,2*num+1);
    if(T[2*num+2]!=zero)
        PostOrderTraverse(T,2*num+2);
    printf("%d ",T[num]);
}


//层序遍历二叉树，就是按数组顺序遍历
status LevelOrderTraverse(bitree T)
{
    if(T[0]==zero) //空树
        return ERROR;

    int i=MAXSIZE; //从后到前找到最大结点处
    while(T[i]==zero)
    {
        i--;
    }

    int j;
    for(j=0;j<i;j++){
        if(T[j]!=zero)
        printf("%d ",T[j]);
    }
    printf("\n");
}


//展示当前二叉树
void ShowBitree(bitree T)
{
    int j,k;
    elemtype e;
    position p;
    for(j=1;j<=BitreeDepth(T);j++){ //层数
        printf("level %d :",j);
        for(k=1;k<=pow(2,j-1);k++){ //该层结点序数
            p.level=j; //位置层赋值
            p.order=k; //位置序数赋值
            e=GetE(T,p); //根据位置获取该值
            if(e!=zero)
            {
                printf("%d:%d ",k,e);
            }
        }
        printf("\n");
    }
    printf("\n");
}


//下面调用main函数验证
int main(void)
{
    status dev;
    elemtype e;
    position p;
    bitree T;
    InitBitree(T);
    CreatBitree(T); 
    dev=BitreeEmptyJudge(T);
    if(dev)
        printf("this tree is empty\n");
    else 
        printf("the depth of this tree is %d\n",BitreeDepth(T));
    
    //层序遍历
    printf("levelorder show:\n");
    LevelOrderTraverse(T);
    //前序遍历
    printf("preorder show:\n");
    PreOrderTraverse(T,0);
    printf("\n");
    //中序遍历
    printf("inorder show:\n");
    InOrderTraverse(T,0);
    printf("\n");
    //后序遍历
    printf("postorder show:\n");
    PostOrderTraverse(T,0);
    printf("\n");

    //修改层号3序号2的结点，先获取，再改为50
    p.level=3;
    p.order=2;
    e=GetE(T,p);
    printf("the origin:%d\n",e);
    e=50;
    Assign(T,p,e);
    ShowBitree(T);
    
    //寻找双亲结点，左孩子，右孩子
    printf("%d's parent is %d\n",e,GetParent(T,e));
    printf("and his left and right child is %d %d\n",GetLeChild(T,e),GetRiChild(T,e));
    printf("his left and right sibling is %d %d\n",GetLeSibling(T,e),GetRiSibling(T,e));

    ClearBitree(T);
    dev=BitreeEmptyJudge(T);
    if(!dev)
    {
        printf("the tree is empty and its depth is %d\n",BitreeDepth(T));
    }
    dev=GetRoot(T,&e);
    if(dev)
    {
        printf("the root is %d\n",e);
    }
    else{
        printf("there is no root\n");
    }
    return 0;
}
