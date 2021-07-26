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
typedef struct linklist //结构体定义和typedef同时用，此后struct linklist相当于link
{
    elemtype data;
    struct linklist * next;
}link; 
typedef struct linklist * linkpoint;  //让linkpoter替换结构标签，就不用struct 标签名 变量名 一起写


//初始化链表
status InitList(linkpoint *L)
{
    *L=(linkpoint)malloc(sizeof(link));
    if(!(*L))  //存储分配失败
        return ERROR;
    
    (*L)->next=NULL; //让它指向空指针
    return OK;
}


//将L置为空表
status ClearList(linkpoint *L)
{
    linkpoint p,t;
    p=(*L)->next;
    while(p)
    {
        t=p->next; //让t去管理p结点的下一个，这样就可以释放p结点
        free(p);
        p=t; //释放完上一个，交出下一个的管理权
    }
    (*L)->next=NULL;
    return OK;
}


//若线性表为空，返回TRUE，否则返回FALSE
status ListEmtyeJudge(linkpoint L)
{
    if(L->next)
        return FALSE;
    else
        return TRUE;
}


//返回结点个数
int ListLen(linkpoint L)
{
    int i=0;
    linkpoint p;
    p=L->next;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}


//找第一个与e相等的数据，返回它是第几项数据元素
int LocateElem(linkpoint L,int e)
{
    int i=0;
    linkpoint p;
    p=L->next;
    while(p)
    {
        i++;
        if(p->data==e)
            return i;
        p=p->next;
    }

    return 0; //如果while的return成功则这个用不到
}


//用e返回L中第i个数据元素的值
status GetElem(linkpoint L,int i,elemtype *e)   //这里的L是一个指针
{
    int cnt;
    linkpoint p; //重新定义一个指针，让它工作
    p=L->next; //让p指针指向链表L的第一个结点
    cnt=1; //让它从第一个结点开始
    while(p&&cnt<i)
    {
        p=p->next; //不断移动指针直到第i个结点
        cnt++;
    }
    if(!p||cnt>i) //第i个元素不存在
        return ERROR;
        
    *e=p->data;
    return OK;


}


//在L中第i个数据元素（ai,头部点不算第一个）之前插入新的数据元素e
status ListInsert(linkpoint *L,int i,elemtype e)
{
    int j;
    linkpoint p,s;
    p=*L;
    j=1; //从头结点开始记第一个
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;

    s=(linkpoint)malloc(sizeof(link));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}


//删除第i个数据元素，并用e返回其值
status ListDelte(linkpoint *L,int i,elemtype *e)
{
    int j;
    linkpoint p,s; //s做替代品
    p=*L;
    j=1;
    while((p->next)&&j<i) //遍历到第i个数据元素
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i)
        return ERROR;
    s=p->next;          //让要s代管理要删除的元素
    p->next=s->next;   //跳过要删除的元素，p直接连接下下个数据元素
    *e=s->data;
    free(s);        //记得释放内存，不然怎么叫删减呢
    return OK;
}


//随机生成n个元素的值，建立带表头结点的单链线性表L（头插法）
status AddListHead(linkpoint *L,int n)
{
    linkpoint p;
    srand(time(0));  //初始化随机种子
    *L=(linkpoint)malloc(sizeof(link)); //表头结点内存申请
    (*L)->next=NULL;
    for(int i=0;i<n;i++){
        p=(linkpoint)malloc(sizeof(link)); //生成新节点
        p->data=rand()%100+1;  //随机生成100以内的数字
        p->next=(*L)->next;
        (*L)->next=p; 
    }
}


//随机生成n个元素的值，建立带表头结点的单链线性表L（尾插法）
status AddListTail(linkpoint *L,int n)
{
    linkpoint p,t;
    *L=(linkpoint)malloc(sizeof(link));
    t=*L;  //t指向尾部的结点
    for(int i=0;i<n;i++){
        p=(linkpoint)malloc(sizeof(link));
        p->data=rand()%100+1;
        t->next=p;
        t=p;  //移动到尾结点
    }
    t->next=NULL;  
}


//展示当前列表
void ShowList(linkpoint L)
{
    printf("now show the list:");
    linkpoint p;
    p=L->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}


//下面通过main调用函数实验
int main(void)
{
    linkpoint La;
    elemtype e;
    status dev; //当前操作是否成功
    int i,j;
    InitList(&La);
    printf("after init,the len is %d\n",ListLen(La));

    //在La的表头向前依次插入1-5
    for(i=1;i<=5;i++){
        ListInsert(&La,1,i);
    }
    
    ShowList(La);
    printf("after insert,the len is %d\n",ListLen(La));
    
    dev=ClearList(&La);
    printf("let's check the list\n");
    if(dev) printf("clear sucessfully\n");

    //在La的表头向后依次插入1-10
    for(i=1;i<=10;i++){
        ListInsert(&La,i,i);
    }
    printf("after insert,the len is %d\n",ListLen(La));
    ListInsert(&La,1,0); //在表头插入0
    printf("after insert,the len is %d\n",ListLen(La));
    ShowList(La);

    GetElem(La,5,&e); //找第五个元素的值
    printf("the fifth number is %d\n",e);

    //寻找3和4的位置
    for(i=3;i<=4;i++){
        j=LocateElem(La,i); //找到返回位置，找不到，返回零
        if(j){
            printf("the number:%d is the %dth\n",i,j);
        }
        else printf("can not find the number:%d\n",i);
    }

    printf("after that,the len is %d\n",ListLen(La));

    //试探删除长度之外和之内的元素
    int k;
    k=ListLen(La); //获取线性表长度 不可直接用La.len 因为La.len会随着删除操作改变
    for(i=k+1;i>=k;i--){
        dev=ListDelte(&La,i,&e);
        if(dev==ERROR){
            printf("fail to delte the %dth number\n",i);
        }
        else printf("delte %dth number:%d sucessfully\n",i,e);

    }
    ShowList(La);
    
    //删除第6个元素
    ListDelte(&La,6,&e);
    ShowList(La);

    //清空线性表，然后用头插法生成20个结点的链表
    ClearList(&La);
    printf("after that,the len is %d\n",ListLen(La));
    AddListHead(&La,20);
    ShowList(La);

    printf("\n");

    //清空线性表，用尾插法生成20个结点的链表
    ClearList(&La);
    printf("after that,the len is %d\n",ListLen(La));
    AddListTail(&La,20);
    ShowList(La);

    return 0;
}
