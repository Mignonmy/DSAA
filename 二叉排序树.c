#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXSIZE 50
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//���濪ʼ�Զ�������
typedef int status;
typedef char elemtype;
typedef struct tree
{
    elemtype data;
    struct tree *lchild,*rchild;
}treelink;
typedef treelink * bitreepoint; //����ָ��ṹ��ָ��


//�����������Ĳ���
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


//�����������Ĳ���
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


//ɾ�������ľ���ʵ��,�������
status Delete(bitreepoint *p)
{
    bitreepoint u,s;

    //��������������Ľ��
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

    //���������Բ��յĽ��
    else{
        u=*p;
        s=(*p)->lchild; //����
        while(s->rchild) //һֱ����
        {
            u=s;
            s=s->rchild;
        }
        (*p)->data=s->data;
        if(u!=*p)
			u->rchild=s->lchild;  //�ؽ�q��������
		else
			u->lchild=s->lchild; //�ؽ�q��������
		free(s);
    }
    return TRUE;
}


//������������ɾ��
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


//������main������֤
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
