#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名字
typedef char elemtype;
typedef int status;
typedef struct list
{
    elemtype data;
    int cur;
}arraylist[10]; //结构数组和typedef的结合


//将一维数组各分量链成一个可放入数据的链表，对第一个和最后一个做特殊处理
//第一个元素（下标为0）的cur放可用空间的第一个结点下标，最后一个元素的cur
//放第一项数据元素的下标，相当于单链表的头结点作用，若链表数值为空，此时为0
status InitList(arraylist L)
{
    for(int i=0;i<MAXSIZE-1;i++){
        L[i].cur=i+1;  //开始不断形成链
    }
    L[MAXSIZE-1].cur=0;  //目前链表数值为空，此处为0
    return OK;
}


//获取分配的空间，返回其下标
int getspaceindex(arraylist L)
{
    int i=L[0].cur;  //获得第一个元素cur的值，也就是第一个可用空间的下标
    if(L[0].cur)      //这个不为零，证明还有可用空间
    {
        L[0].cur=L[i].cur;  //把原本可用空间代理的下一个可用空间的下标给第一个元素
    }     
    return i;
}


//获取L的元素个数
int ListLen(arraylist L)
{
    int index;
    int cnt=0;
    index=L[MAXSIZE-1].cur;  //获取第一个数据元素的下标
    while(index)
    {
        index=L[index].cur; //不断获取其代管理元素下标
        cnt++;
    }
    return cnt;
}


//在第i个数据元素之前插入数据e
status ListInsert(arraylist L,int i,elemtype e)
{
    int j,k,cnt; //cnt用作计数，t用作记录可用空间下标
    k=MAXSIZE-1; //k首先初始化为线性表最后一个元素下标，以便获取它记录的第一个数据元素下标
    
    if(i<1||i>ListLen(L)+1)
        return ERROR;
    j=getspaceindex(L);  //获得可用空间下标
    if(j)
    {
        L[j].data=e;
        for(cnt=1;cnt<=i-1;cnt++) //找到第i个数据元素之前位置
            k=L[k].cur;   //从最后一个元素记录的下标开始不断遍历
        
        //找到之后，把原本第i个元素之前的那个元素代管的下一个元素下标（第i个元素下标）
        L[j].cur=L[k].cur;   //给新插入元素代管，毕竟插进来之后，新元素后面就是第i个元素

        L[k].cur=j; //同时告诉原来的第i-1个元素，你要代管新插入的元素，记录他的下标
        return OK;
    }
    
    return ERROR;  //如果获取可用空间失败，返回ERROR
}


//把删除的那一项回收至可用空间内
void cycleintospace(arraylist L,int index)
{
    L[index].cur=L[0].cur; //让被“删除”的元素回收至可用空间最前面
    L[0].cur=index;  //此时第一个可用空间下标就是刚刚被“删除”的元素的下标
}


//删除第i个数据元素
status ListDelte(arraylist L,int i)
{
    int j,k;
    k=MAXSIZE-1; //k首先初始化为线性表最后一个元素下标，以便获取它记录的第一个数据元素下标
    if(i<1||i>ListLen(L))
        return ERROR;

    for(j=1;j<=i-1;j++) //这里j用作计数
    {
        k=L[k].cur;    //获得管理要删除元素的那个元素的下标，毕竟它有记录着删除元素的下标
    }
    
    j=L[k].cur;   //记录要删除元素的下标 这里j应该是5
    L[k].cur=L[j].cur;  //让第i-1个数据元素代管理第i个数据元素原本要管理的
    
    cycleintospace(L,j);
    
    return OK;
}


//展示当前线性表
void ShowList(arraylist L)
{
    printf("now show the list:\n");
    int index=L[MAXSIZE-1].cur;
    while(index)
    {
        printf("%c ",L[index].data);
        index=L[index].cur;
    }
    printf("\n");
}


//下面用main函数测试
int main(void)
{
    arraylist La;
    status dev; //当前操作是否成功
    InitList(La);
    printf("after that,the len is %d\n",ListLen(La));

    //不断在表头放入元素
    ListInsert(La,1,'F');
    ListInsert(La,1,'E');
    ListInsert(La,1,'D');
    ListInsert(La,1,'B');
    ListInsert(La,1,'A');
    printf("after insert,the len is %d\n",ListLen(La));
    ShowList(La);

    //在B和D之间插入C
    ListInsert(La,3,'C');
    printf("after insert,the len is %d\n",ListLen(La));
    ShowList(La);

    //删除A
    ListDelte(La,1);
    ShowList(La);
    return 0;
}
