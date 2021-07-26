#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名称
typedef int elemtype;
typedef int status;
typedef struct
{
    elemtype data[MAXSIZE];
    int top; //可操作的元素下标
}sqstack;


//构造一个空栈S
status InitStack(sqstack *S)
{
    S->top=-1;
    return OK;
}


//把栈设为空栈
status ClearStack(sqstack *S)
{
    S->top=-1;
    return OK;
}


//若栈为空，返回TRUE,否则返回FALSE
status StackEmptyJudge(sqstack S)
{
    if(S.top==-1)
        return TRUE;
    else
        return FALSE;
}


//返回栈内的元素个数
int StackLen(sqstack S)
{
    return S.top+1;
}


//若栈存在且非空，用e返回S的栈顶元素
status GetTop(sqstack S,elemtype *e)
{
    if(S.top==-1)  //空栈
        return ERROR;
    else
        *e=S.data[S.top];
    return OK;
}


//插入新元素e，并使其成为栈顶元素
status Push(sqstack *S,elemtype e)
{   
    if(S->top==MAXSIZE-1)  //栈满
        return ERROR;

    S->top++; //记录为下一个可操作下标
    S->data[S->top]=e; //赋值
    return OK;
}


//删除栈顶元素，用e返回其值
status Pop(sqstack *S,elemtype *e)
{
    if(S->top==-1)
        return ERROR;
    
    *e=S->data[S->top]; //记录要返回的值
    S->top--; //可操作下标改变
    return OK;
}


//展示当前栈的元素
void ShowStack(sqstack S)
{
    printf("now show the stack:");
    int i=0;
    while(i<=S.top)
    {
        printf("%d ",S.data[i++]);
    }
    printf("\n");
}


//下面用main函数验证以上代码
int main(void)
{
    int j;
    elemtype e;
    sqstack Sa;
    status dev;  //当前操作是否成功

    //初始化一个空栈并插入1-10
    if(InitStack(&Sa)==OK)
    {
        for(j=1;j<=10;j++){
            Push(&Sa,j);
        }
    }
    ShowStack(Sa);
    
    //弹出栈顶元素
    Pop(&Sa,&e);
    ShowStack(Sa);

    //获取栈顶元素值
    GetTop(Sa,&e);
    printf("the top elem of this stack is %d\n",e);

    //获取元素个数
    printf("the len of this stack is %d\n",StackLen(Sa));

    //清空
    dev=ClearStack(&Sa);
    printf("let's check the list\n");
    if(dev) printf("clear sucessfully\n");

    return 0;
}
