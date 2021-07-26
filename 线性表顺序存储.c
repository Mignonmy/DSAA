//线性表第i个位置在数组中下标索引值为i-1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//下面开始自定义类型名字
typedef int elemtype;
typedef struct list
{
    elemtype data[MAXSIZE]; 
    int len; //线性表当前长度
}sqlist;
typedef int status; //别紧张，换个名字而已，好看


//初始化操作，建立一个空的线性表L
status InitList(sqlist *L)
{
    L->len=0;
    return OK;
}


//若线性表为空，返回TRUE，否则返回FALSE
status ListEmptyJudge(sqlist L)
{
    if(L.len==0)
        return TRUE;
    else 
        return FALSE;
}


//将线性表清空
status ClearList(sqlist *L)
{
    L->len=0;
    return OK;
}


//返回线性表元素个数
int ListLen(sqlist L)
{
    return L.len;
}


//将线性表L中的第i个位置元素值返回给e
status GetElem(sqlist L,int i,elemtype *e)
{
    if(L.len==0||i<1||i>L.len) //长度为零，下标不符，长度过大都不行
    return ERROR;
    else{
        *e=L.data[i-1];
        return OK;
    }
}


//在线性表L中查找与给定值e相等的元素，查找成功，返回该元素在表中
//序号，失败，返回零
int LocateElem(sqlist L,elemtype e)
{
    int index;
    if(L.len==0)
        return 0;
    for(index=0;index<L.len;index++){
        if(L.data[index]==e)
            break;
    }
    if(index>=L.len)
        return 0;

    return index+1; //位置
}


//在线性表L中的第i个位置lalal插入新元素e
status ListInsert(sqlist *L,int i,elemtype e)
{
    int index;
    if(L->len==MAXSIZE) //顺序线性表已满
        return ERROR;
    if(i<1||i>L->len+1) //既不是中间插入也不是首部尾部插入
        return ERROR;

    if(i<=L->len)
    {
        for(index=L->len-1;index>=i-1;index--){   //i-1是为迎合数组下标从0开始
            L->data[index+1]=L->data[index]; //将要插入位置后的元素整体向后移一位
    }
    }
        L->data[i-1]=e; //已经空出来，可以放入新元素
        L->len++;

        return OK;
    
}


//删除线性表L中的第i个位置元素，并用e返回其值
status ListDelte(sqlist *L,int i,elemtype *e)
{
    int index;
    if(L->len==0) //线性表为空
        return ERROR;
    if(i<1||i>L->len) //删除位置不正确
        return ERROR;
    
    *e=L->data[i-1]; //记录删除元素
    if(i<L->len)  //如果删除的位置不是最后一个，则需整体往前移一位
    {
        for(index=i;index<L->len;index++){
            L->data[index-1]=L->data[index];
        }
    }

    L->len--;
    return OK;

}


//展示当前线性表
void ShowList(sqlist L)
{
    printf("now show the list:");
    for(int i=0;i<L.len;i++){
        printf("%d ",L.data[i]);
    }
    printf("\n");
}

//下面用主函数调用上面的函数试验，顺便演示怎么用
int main(void)
{
    sqlist La;
    elemtype e;
    status dev; //当前操作是否成功
    int i,j;
    InitList(&La);
    printf("after init,the len is %d\n",La.len);

    //在La的表头向前依次插入1-5
    for(i=1;i<=5;i++){
        ListInsert(&La,1,i);
    }
    
    ShowList(La);
    printf("after insert,the len is %d\n",La.len);
    
    dev=ClearList(&La);
    printf("let's check the list\n");
    if(dev) printf("clear sucessfully\n");

    //在La的表头向后依次插入1-10
    for(i=1;i<=10;i++){
        ListInsert(&La,i,i);
    }
    printf("after insert,the len is %d\n",La.len);
    ListInsert(&La,1,0); //在表头插入0
    printf("after insert,the len is %d\n",La.len);
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

    printf("after that,the len is %d\n",La.len);

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
    return 0;
}
