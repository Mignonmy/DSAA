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
typedef struct tree
{
    elemtype data;
    struct tree *lchild,*rchild;
}treelink;
typedef treelink * bitreepoint; //定义指向结构的指针


//二叉排序树的查找
status BSTSearch(bitreepoint T,int key,bitreepoint F,bitreepoint *p)
{
    if(!T)
    {
        *p=F;
        return FALSE;
    }
    else if(key==T->data)
    {
        *p=T;
        return TRUE;
    }
    else if(key<T->data)
        return BSTSearch(T->lchild,key,T,p);
    else
        return BSTSearch(T->rchild,key,T,p);
}


//二叉排序树的插入
status BSTInsert(bitreepoint *T,int key)
{
    bitreepoint p,s;
    if(!BSTSearch(*T,key,NULL,&p))
    {
        s=(bitreepoint)malloc(sizeof(treelink));
        s->data=key;
        s->lchild=s->rchild=NULL;

        if(!p)
            *T=s;
        else if(key<p->data)
            p->lchild=s;
        else
            p->rchild=s;
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}


//删除函数的具体实现,三种情况
status Delete(bitreepoint *p)
{
    bitreepoint u,s;

    //仅有左或又子树的结点
    if((*p)->rchild==NULL)
    {
        u=*p;
        *p=(*p)->lchild;
        free(u);
    }
    else if((*p)->lchild==NULL)
    {
        u=*p;
        *p=(*p)->rchild;
        free(u);
    }

    //左右子树皆不空的结点
    else{
        u=*p;
        s=(*p)->lchild; //向左
        while(s->rchild) //一直向右
        {
            u=s;
            s=s->rchild;
        }
        (*p)->data=s->data;
        if(u!=*p)
			u->rchild=s->lchild;  //重接q的右子树
		else
			u->lchild=s->lchild; //重接q的左子树
		free(s);
    }
    return TRUE;
}


//二叉排序树的删除
status BSTDelete(bitreepoint *T,int key)
{
    if(!*T)
        return FALSE;
    else
    {
        if(key==(*T)->data)
            return Delete(T);
        else if(key<(*T)->data)
            return BSTDelete(&(*T)->lchild,key);
        else
            return BSTDelete(&(*T)->rchild,key);
    }
}


//下面用main函数验证
int main()
{
    int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	bitreepoint T=NULL;
	
	for(i=0;i<10;i++)
	{
		BSTInsert(&T, a[i]);
	}
	BSTDelete(&T,93);
	BSTDelete(&T,47);

	return 0;
}
