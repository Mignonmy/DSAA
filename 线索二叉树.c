//本次代码以中序线索二叉树为例，前序，后序类似，顺序不一样而已
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型
typedef int status;
typedef char elemtype;
typedef enum{child,prepost} info;
typedef struct bitree 
{
    elemtype data;
    struct bitree *lchild,*rchild;
    info left;
    info right;
}threadbitree; //定义线索二叉树
typedef threadbitree * threadbitreepoint; //定义指向线索二叉树结构的指针


//全局变量
threadbitreepoint pre=NULL;
elemtype zero='#';


//第一次线索化
//生成二叉树，便完成child的索引,即有左右孩子left值赋为0
status CreatThrearBitree(threadbitreepoint *T)
{
    elemtype ch;
    scanf("%c",&ch); //不断获取值

    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(threadbitreepoint)malloc(sizeof(threadbitree));
        if(!(*T))
            exit(OVERFLOW); //系统内粗不够
        (*T)->data=ch;
        CreatThrearBitree(&(*T)->lchild);
        if((*T)->lchild) //有左孩子
            (*T)->left=child; //0值赋予
        CreatThrearBitree(&(*T)->rchild);
        if((*T)->rchild) //有右孩子
            (*T)->right=child;
    }
    return OK;
}


//第二次线索化
//完成剩下的中序遍历索引，即1（prepost）值得赋予
//二叉树已完成建立，此处只需要通过头指针不断找到相应结点，对相应结点进行线索化
//不需要整体链起来，因此不需要传递二级指针
void InorderThread(threadbitreepoint p)
{
    if(p)
    {
        InorderThread(p->lchild); //一路向左
        if(p->lchild==NULL) //左孩子为空
        {
            p->lchild=pre;   //赋予前驱结点，pre是全局变量，开始是NULL，
            p->left=prepost; //对于遍历的第一个结点会赋予头结点（见下文），之后的会有前驱结点的
        }
        //记住这里是中序索引，是先遍历左子树再回到结点之后再到右子树，p为当前结点
        //此时pre不为空，即p有左孩子，这里已经是最深的左孩子了，如果这个左孩子向下还有右孩子，应在这时继续向下
        //如果没有，说明p是这个左孩子的后继结点，因为是中序遍历
        if(pre!=NULL&&pre->rchild==NULL)
        {
            pre->rchild=p;
            pre->right=prepost;
        }
        pre=p; //更替相应结点的前驱结点
        InorderThread(p->rchild); //向右遍历
    }
}


//第三次线索化
//添加头结点，完善书本p164页四个剩下的指向，①是头结点的左指针指向第一个左孩子结点
//②是头结点的右指针指向中序遍历的最后一个结点，③是中序遍历的第一个结点的左指针指向头结点，在第二次线索化已完成
//④是中序遍历的最后一个结点的右指针指向头结点
status AllThread(threadbitreepoint *T,threadbitreepoint p)
{
    (*T)=(threadbitreepoint)malloc(sizeof(threadbitree)); //头结点内存申请
    if((*T)==NULL)
        exit(OVERFLOW);

    (*T)->left=child; //0，1 分配
    (*T)->right=prepost;
    (*T)->rchild=(*T); //右指针回指

    if(*T==NULL) //树空
        (*T)->lchild=(*T); //头结点左指针指向自己
    else
    {
        (*T)->lchild=p; //完成①
        pre=(*T); //让头结点成为前驱
        InorderThread(p);
        //到这一步p已经是NULL了，pre是中序遍历的最后一个结点
        pre->rchild=(*T); //完成④
        pre->right=prepost;
        (*T)->rchild=pre; //完成②
    }
    return OK;
}


//中序遍历方式展示二叉树数据，此处没有用递归方式遍历
status InOrderTraverse(threadbitreepoint T)
{
    threadbitreepoint p;
    p=T->lchild; //让p指向第一个结点
    while(p!=T) //当两者相等，意味着回到最初点，不再遍历
    {
        while(p->left==child)
        {
            p=p->lchild; //一路向左
        }
        printf("%c",p->data);
        while(p->right==prepost&&p->rchild!=T) //此结点有右孩子，参考71-73行注释的第二行注释
        {
            p=p->rchild; //来到这个右孩子
            printf("%c",p->data);
        }
        p=p->rchild; //来到后继结点
    }
    return OK;
}


//下面调用main函数验证
int main(void)
{
    threadbitreepoint H,T;
    printf("please enter data (for example:ABDH##I##EJ###CF##G##) \n");
    CreatThrearBitree(&T);

    AllThread(&H,T);

    printf("inorder show:\n");
    InOrderTraverse(H);
    return 0;
}
