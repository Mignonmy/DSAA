#include <stdio.h>
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
    int top1; //可操作的元素下标
    int top2;
}sqdbstack;


//初始化栈
status InitStack(sqdbstack *S)
{
    S->top1=-1;
    S->top2=MAXSIZE;
    return OK;
}


//把栈设为空栈
status ClearStack(sqdbstack *S)
{
    S->top1=-1;
    S->top2=MAXSIZE;
    return OK;
}


//若为空栈，返回TRUE，否则返回FALZE
status StackEmptyJudge(sqdbstack S)
{
    if(S.top1==-1&&S.top2==MAXSIZE)
        return TRUE;
    else
        return FALSE;
}


//获取栈内元素个数
int StackLen(sqdbstack S)
{
    return (S.top1+1)+(MAXSIZE-S.top2);
}


//插入元素e为新的栈顶元素
status Push(sqdbstack *S,elemtype e,int stacknum)
{
    if(S->top1+1==S->top2)  //栈满
        return ERROR;
    
    if(stacknum==1)
        S->data[++S->top1]=e; //加1之后再赋值

    else if(stacknum==2)
        S->data[--S->top2]=e;

    return OK;
}


//删除栈顶元素，并用e返回其值
status Pop(sqdbstack *S,elemtype *e,int stacknum)
{
    if(stacknum==1){  //先针对于栈1的情况
        if(S->top1==-1)
            return ERROR;
        
        *e=S->data[S->top1--]; //先赋值再减1 
    }
    else if(stacknum==2)  //现在讨论针对与栈2情况
    {
        if(S->top2==MAXSIZE)
            return ERROR;

        *e=S->data[S->top2++]; //先赋值再加1
    }

    return OK;
}


//展示当前元素
void ShowStack(sqdbstack S)
{
    printf("now show the stack:");
    int i=0;
    while(i<=S.top1)
    {
        printf("%d ",S.data[i++]);
    }
    i=S.top2;
    while(i<MAXSIZE)
    {
        printf("%d ",S.data[i++]);
    }
    printf("\n");
}

//下面调用main函数验证
int main(void)
{
    int j;
    sqdbstack Sa;
    elemtype e;
    status dev;
    
    //初始化栈，并压1-5至栈1，18，19，20进栈2
    if(InitStack(&Sa)==OK)
    {
        for(j=1;j<=5;j++){
            Push(&Sa,j,1);
        }
        for(j=MAXSIZE;j>=MAXSIZE-2;j--){
            Push(&Sa,j,2);
        }
    }
    ShowStack(Sa);
    printf("the len of this stack is %d\n",StackLen(Sa));
    
    //弹出栈2的栈顶元素，即18
    Pop(&Sa,&e,2);
    ShowStack(Sa);

    //插入6-18
    for(j=6;j<=MAXSIZE-2;j++){
        Push(&Sa,j,1);
    }
    ShowStack(Sa);

    dev=Push(&Sa,100,1);
    if(!dev) printf("this stack is full\n");

    //清空栈
    dev=ClearStack(&Sa);
    if(dev) printf("clear sucessfully\n");

    return 0;
}
