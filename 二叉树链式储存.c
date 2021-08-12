#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define zero ' '

//下面开始自定义类型
typedef int status;
typedef char elemtype;
typedef char string[50]; 
typedef struct tree
{
    elemtype data;
    struct tree *lchild,*rchild;
}treelink;
typedef treelink * bitreepoint; //定义指向结构的指针

//全局变量str
string str;
int strindex=1;

//用数组存放字符串
status CreatStr(string S,char *chars)
{
    if(strlen(chars)>MAXSIZE) //字符长度大于数组最大长度
    {
        printf("this string is overlen\n");
    }
    else
    {
        S[0]=strlen(chars); //0号用来存放字符串长度
        for(int i=1;i<=S[0];i++)
        {
            S[i]=*(chars+i-1); //不断赋值数组
        }
        return OK;
    }
}
//初始化二叉树
status InitBitree(bitreepoint *T)
{
    *T=NULL;
    return OK;
}


//创造本次的二叉树
void CreatBitree(bitreepoint *T)
{
    elemtype ch;
    ch=str[strindex++];
    if(ch=='#') //若是#，则不申请结点，直接让指向结构的指针的指针为空
        *T=NULL;
    else
    {
        *T=(bitreepoint)malloc(sizeof(treelink)); //申请结构
        if(!*T)
            exit(OVERFLOW); //系统内存不够
        (*T)->data=ch;
        CreatBitree(&(*T)->lchild); //构造左子树
        CreatBitree(&(*T)->rchild); //构造右子树
    }
}


//清掉二叉树
void DestroyBitree(bitreepoint *T)
{
    if(*T) //像后序遍历一样，不断遍历，指针不断改变指向，释放
    {
        if((*T)->lchild) 
            DestroyBitree(&(*T)->lchild);
        if((*T)->rchild)
            DestroyBitree(&(*T)->rchild);
        free(*T);
        *T=NULL;
    }
}
#define ClearBitree DestroyBitree//链式储存摧毁树就是清空树


//判断二叉树是否为空
status BitreeEmptyJudge(bitreepoint T)
{
    if(T)
        return FALSE;
    else
        return TRUE;
}


//获取二叉树的深度
int BitreeDepth(bitreepoint T) //不断递，去到最深处，归回左右子树中较大的一边+1
{
    int ld,rd; //记录左，右子树的深度
    if(T==NULL)
        return 0;
    ld=BitreeDepth(T->lchild);
    rd=BitreeDepth(T->rchild);
    
    return ld>rd? ld+1:rd+1;    
}


//获得根的值,空根返回zero
elemtype GetRoot(bitreepoint T)
{
    if(BitreeEmptyJudge(T)) //根为空
        return zero;
    else
        return T->data;
}


//获得p指针指向的结点的数据域值
elemtype GetData(bitreepoint p)
{
    return p->data;
}


//为p指针指向的结点赋值e
status Assign(bitreepoint p,elemtype e)
{
    p->data=e;
}


//前序遍历
void PreOrderTraverse(bitreepoint T)
{
    if(T==NULL)
        return;
    
    printf("%c",T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}


//中序遍历
void InOrderTraverse(bitreepoint T)
{
    if(T==NULL)
        return;
    
    InOrderTraverse(T->lchild);
    printf("%c",T->data);
    InOrderTraverse(T->rchild);
}


//后序遍历
void PostOrderTraverse(bitreepoint T)
{
    if(T==NULL)
        return;
    
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c",T->data);
}


//下面调用main函数验证
int main(void)
{
    status dev;
    bitreepoint T; //用指向结构的指针操作结构
    elemtype e;

    InitBitree(&T);
    CreatStr(str,"ABDH#K###E##CFI###G#J##");
    CreatBitree(&T);

    dev=BitreeEmptyJudge(T);
    if(!dev) //树不空
        printf("the depth of this tree is %d\n",BitreeDepth(T));
    
    //获取树的根
    e=GetRoot(T);
    printf("the root is %c\n",e);
    //前中后序遍历
    printf("preorder show:\n");
    PreOrderTraverse(T);
    printf("\n");

    printf("inorder show:\n");
    InOrderTraverse(T);
    printf("\n");

    printf("postorder show:\n");
    PostOrderTraverse(T);
    printf("\n");

    //清空二叉树
    ClearBitree(&T);
    dev=BitreeEmptyJudge(T);
    if(dev)
        printf("the depth of this tree is %d\n",BitreeDepth(T));
    
    return 0;
}
