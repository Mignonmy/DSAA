#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名字
typedef int elemtype;
typedef int status;
typedef struct linklist     //此为真正链表
{
    elemtype data;
    struct linklist * next;
}linkstack;

typedef linkstack * linkpoint;

typedef struct      //此为方便操作链表定义的
{
    linkpoint top;
    int cnt;
}forlinkstack;


//构造一个空栈
status InitStack(forlinkstack *P)
{
    P->top=(linkpoint)malloc(sizeof(linkstack));
    if(!P->top)
        return ERROR;
    
    P->top=NULL;
    P->cnt=0;
    return OK;
}


//空栈
status ClearStack(forlinkstack *P)
{
    linkpoint s,temp;
    s=P->top;   //先让一个指针指向栈顶元素
    while(s)
    {
        temp=s;  //让一个替代栈顶指针
        s=s->next; //接着栈顶指针移向下一位
        free(temp); //释放原本的栈顶
    }
    P->cnt=0;
    return OK;

}


//若为空栈，返回TRUE，否则返回FALSE
status StackEmptyJudge(forlinkstack P)
{
    if(P.cnt==0)
        return TRUE;
    else
        return FALSE;
}


//获取栈内元素个数
status StackLen(forlinkstack P)
{
    return P.cnt;
}


//获取栈顶元素，用e返回其值
status GetTop(forlinkstack P,elemtype *e)
{
    if(P.top==NULL)
        return ERROR;
    else 
        *e=P.top->data;   //P为管理栈顶指针和栈内元素个数的结构 P.top为栈顶指针
    return OK;
}


//插入元素e为新的栈顶元素
status Push(forlinkstack *P,elemtype e)
{
    linkpoint s=(linkpoint)malloc(sizeof(linkstack));
    s->data=e; //先为新申请的结构的数据域赋值
    s->next=P->top; //让原来的栈顶元素成为新元素的后继点
    P->top=s; //改变栈顶指针，让其指向新元素
    P->cnt++;
    return OK;
}


//若栈不空，则删除栈顶元素，用e返回其值
status Pop(forlinkstack *P,elemtype *e) //这时候P是指向结构的指针
{
    linkpoint temp;
    if(StackEmptyJudge(*P))
        return ERROR;
    
    *e=P->top->data;  //记录要删除的栈顶元素的值
    temp=P->top; //让一个指针替代栈顶指针
    P->top=P->top->next; //改变栈顶指针至下一位
    free(temp); //释放原本栈顶指针指向的地方
    P->cnt--;
    return OK;
}


//展示当前栈内元素
status ShowStack(forlinkstack P)
{
    printf("now show the stack:");
    linkpoint s;
    s=P.top; //让s指针成为栈顶指针
    while(s)
    {
        printf("%d ",s->data);
        s=s->next;
    }
    printf("\n");
}


//下面调用main函数验证
int main(void)
{
    forlinkstack P; //直接定义一个管理结构的即可，结构可在函数内开辟或删除
    int j;
    elemtype e;
    int dev; //当前操作是否成功

    //初始化栈
    InitStack(&P);

    //插入1-10
    for(j=1;j<=10;j++){
        Push(&P,j);
    }
    ShowStack(P);

    //弹出栈顶元素
    Pop(&P,&e);
    printf("pop %d out\n",e);
    printf("the len of this stack is %d\n",StackLen(P));
    ShowStack(P);

    //获取栈顶元素
    GetTop(P,&e);
    printf("the top of this stack is %d\n",e);

    //清空
    dev=ClearStack(&P);
    if(dev)
        printf("clear sucessfully.\n");

    return 0;
}
