#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 50

//下面开始自定义类型
typedef int status;
typedef char elemtype;
typedef char string[MAXSIZE+1];


//生成一个与chars相等的串T
status CreatEqualStr(string T,char *chars)
{
    if(strlen(chars)>MAXSIZE) //要创造的字符长度判断
        return ERROR;
    else{
        T[0]=strlen(chars); //记录字符长度

        for(int i=1;i<=T[0];i++){
            T[i]=*(chars+i-1);  //这里-1是为弥补i不从0开始而从1开始导致的指针提前加了1
        }
        return OK;
    }
}


//获取字符串长度
int StrLen(string S)
{
    return S[0];
}


//清空字符串
status ClearStr(string S)
{
    S[0]=0;
    return OK;
}


//朴素模式匹配算法
//返回在串S中，字串T从第position个字符开始的位置，若无，返回0
status Index1(string S,string T,int position)
{
    int index1,index2; //分别记录主串与子串的下标
    index1=position;
    index2=1;
    while(index1<=S[0]&&index2<=T[0]) //短的一方超过后停止
    {
        if(S[index1]==T[index2]){
            index1++;
            index2++;
        }
        else
        {
            index1=index1-index2+2; //下标返回至上次首次匹配的下一位
            index2=1;
        }
    }
    if(index2>T[0])  //完全匹配好最后index2的值是比子串长度大1的，因为相等会+1
        return index1-T[0]; //匹配结束位置下一位反减子串长度得开始位置
    else
        return 0;
}


//生成对应的next数组
void GetNext(string S,int *next)
{
    int i; //遍历数组
    int m; //用来与下标为i的值进行比较，当匹配失败，也作回溯至已匹配好的公共前后缀的下一位
    //i与m实际上分别是待匹配前缀的最后一个和后缀的最后一个
    //前缀一定包括数组的第一个，后缀一定包括待匹配后缀的最后一个
    i=1;
    m=0;
    next[1]=0;
    while(i<S[0])
    {
        if(m==0||S[i]==S[m]) //当m真的回溯至0时，证明公共前后缀不存在，此时应像朴素模式匹配一样
        {                     //直接往后移
            i++;
            m++;
            next[i]=m; //这里记录着已匹配好的公共前后缀的下一位
        }
        else
        {
            m=next[m]; //回溯至已匹配好的公共前后缀的下一位，看看是否能继续增加公共前后缀
        }
    }
}


//返回子串T在主串S中第position个字符之后出现的位置
int KMPIndex1(string S,string T,int position)
{
    int i; //遍历主串S
    i=position;
    int m=1; //遍历子串T，从第一个字符开始，必要时进行回溯
    int next[MAXSIZE+1];
    GetNext(S,next);
    while(i<=S[0]&&m<=T[0])
    {
        if(m==0||S[i]==T[m])
        {
            i++; //匹配成功或没有公共前后缀
            m++; //子串主串同时往后移
        }
        else
        {
            m=next[m]; //跳过已匹配好的，这里应存在公共前后缀，后缀可以对应主串后面的，既然相等
                        //此时可以直接从前缀的下一位开始匹配，不需要重复匹配相等公共前后缀
        }
    }
    if(m>T[0])
        return i-T[0];
    else
        return 0;

}


//生成对应的nextval数组
void GetNextval(string S,int *nextval)
{
    int i; 
    int m;
    i=1;
    m=0;
    nextval[1]=0;
    while(i<S[0])
    {
        if(m==0||S[i]==S[m]) //当m真的回溯至0时，证明公共前后缀不存在，此时应像朴素模式匹配一样
        {                     //直接往后移
            i++;
            m++;
            if(S[i]!=S[m])
            {
                nextval[i]=m; //这里记录着已匹配好的公共前后缀的下一位
            }
            else
            {
                nextval[i]=nextval[m];
            }
        }
        else
        {
            m=nextval[m]; //回溯至已匹配好的公共前后缀的下一位，看看是否能继续增加公共前后缀
        }
    }
}


//返回子串T在主串S中第position个字符之后出现的位置
int KMPIndex2(string S,string T,int position)
{
    int i; //遍历主串S
    i=position;
    int m=1; //遍历子串T，从第一个字符开始，必要时进行回溯
    int nextval[MAXSIZE+1];
    GetNextval(S,nextval);
    while(i<=S[0]&&m<=T[0])
    {
        if(m==0||S[i]==T[m])
        {
            i++; //匹配成功或没有公共前后缀
            m++; //子串主串同时往后移
        }
        else
        {
            m=nextval[m]; //跳过已匹配好的，这里应存在公共前后缀，后缀可以对应主串后面的，既然相等
                        //此时可以直接从前缀的下一位开始匹配，不需要重复匹配相等公共前后缀
        }
    }
    if(m>T[0])
        return i-T[0];
    else
        return 0;
}


//展示next数组
void ShowNext(int next[],int len)
{
    int i;
    for(i=1;i<=len;i++){
        printf("%d",next[i]);
    }
    printf("\n");
}


//展示nextval数组
void ShowNextval(int nextval[],int len)
{
    int i;
    for(i=1;i<=len;i++){
        printf("%d",nextval[i]);
    }
    printf("\n");
}


//展示当前字符串内容
void ShowStr(string S)
{
    printf("now show the string:\n");
    for(int i=1;i<=S[0];i++){
        printf("%c",S[i]);
    }
    printf("\n");
}


//下面调用main函数验证
int main(void)
{
    int len;
    int *p;
    string S1,S2;

    //生成一个abcdex串
    CreatEqualStr(S1,"abcdex");
    ShowStr(S1);
    len=StrLen(S1);
    p=(int *)malloc((len+1)*sizeof(int));
    GetNext(S1,p);
    printf("next:");
    ShowNext(p,len);
    printf("\n");

    //生成一个abcabx串
    CreatEqualStr(S1,"abcabx");
    ShowStr(S1);
    len=StrLen(S1);
    p=(int *)malloc((len+1)*sizeof(int));
    GetNext(S1,p);
    printf("next:");
    ShowNext(p,len);
    printf("\n");

    //生成一个aaaaaaaab串
    CreatEqualStr(S1,"aaaaaaaab");
    ShowStr(S1);
    len=StrLen(S1);
    p=(int *)malloc((len+1)*sizeof(int));
    GetNext(S1,p);
    printf("next:");
    ShowNext(p,len);
    GetNextval(S1,p);
    printf("nextval:");
    ShowNextval(p,StrLen(S1));
    printf("\n");

    //生成一个ababaaaba串
    CreatEqualStr(S1,"ababaaaba");
    ShowStr(S1);
    len=StrLen(S1);
    p=(int *)malloc((len+1)*sizeof(int));
    GetNext(S1,p);
    printf("next:");
    ShowNext(p,len);
    GetNextval(S1,p);
    printf("nextval:");
    ShowNextval(p,StrLen(S1));
    printf("\n");

    //匹配
    CreatEqualStr(S1,"00000000000000000000000000000000000000000000000001");
    ShowStr(S1);
    CreatEqualStr(S2,"0000000001");
    ShowStr(S2);
    printf("S1 is on %dth as same sa S2\n",Index1(S1,S2,1));
    printf("S1 is on %dth as same sa S2\n",KMPIndex1(S1,S2,1));
    printf("S1 is on %dth as same sa S2\n",KMPIndex2(S1,S2,1));
    return 0;
}
