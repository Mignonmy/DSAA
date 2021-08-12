#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20

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


//由串S复制到串T
status StrCopy(string T,string S)
{
    for(int i=0;i<=S[0];i++){
        T[i]=S[i];
    }
    return OK;
}


//若S是空串，返回TRUE，否则返回FALSE
status StrEmptyJudge(string S)
{
    if(S[0]==0)
        return TRUE;
    else
        return FALSE;
}


//若S>T，返回时>0,S=T，返回值=0,S<T，返回值<0，注意这里判断的是字母的大小
int StrCompare(string S,string T)
{
    for(int i=1;i<=S[0]&&i<=T[0];i++){
        if(S[i]!=T[i])
            return S[i]-T[i]; //这里是不相等
    }
    return 0; //如果循环内都没有return过，即字符串相等
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


//用T返回S1和S2连接成的新串，无截断返回OK,截断时返回ERROR
status StrConcat(string T,string S1,string S2)
{
    if(S1[0]+S2[0]<=MAXSIZE)
    {
        for(int i=1;i<=S1[0];i++){ //先连接第一个字符串
            T[i]=S1[i];
        }
        for(int i=1;i<=S2[0];i++){ //第二个字符串
            T[S1[0]+i]=S2[i];
        }
        T[0]=S1[0]+S2[0]; //字符串总长
        return OK;
    }
    else
    {
        for(int i=1;i<=S1[0];i++){ //第一个肯定是正常的
            T[i]=S1[i];
        }
        for(int i=1;i<=MAXSIZE-S1[0];i++){
            T[S1[0]+i]=S2[i];
        }
        T[0]=MAXSIZE;
        return ERROR;
    }
}


//用sub返回S串中从第position个字符（包括）开始的长度为len的字串
status SubStr(string sub,string S,int position,int len)
{
    if(position<1||position>S[0]-len+1||position>S[0]||len<0){ //第二个判断条件保证
        return ERROR; //在取后面字符串时，从position开始到字符串结束位置有len长度可取，不至于不到len就截断
    }
    for(int i=1;i<=len;i++){
        sub[i]=S[position+i-1]; //同样这里-1也是为弥补i从1开始的缺陷
    }
    sub[0]=len;
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


//返回在串S中，字串T从第position个字符开始的位置，若无，返回0
status Index2(string S,string T,int position)
{
    int len1,len2;
    string sub; //提取出来的字符串
    int record;  //记录下标
    
    if(position>0)
    {
        len1=StrLen(S);
        len2=StrLen(T);
        record=position; //先从指定位置开始

        while(record<=len1-len2+1){ //参考SubStr第二个条件判断含义
            SubStr(sub,S,record,len2);
            if(StrCompare(T,sub)!=0){
                record++; //抽取出来与子串匹配不成功，下移一位
            }
            else
                return record; //匹配成功
        }
    }
    return 0; //找不到，返回0
}


//在主串S中第position个字符之前插入子串T，完全插入返回TRUE，否则返回FALSE
status StrInsert(string S,string T,int position)
{
    int i,j;
    if(position<1||position>S[0]+1) //即不在内部也不在字符串尾部
        return ERROR;
    if(S[0]+T[0]<=MAXSIZE) //完全插入
    {
        for(i=S[0];i>=position;i--){
            S[i+T[0]]=S[i];   //把需要插入的长度的字符串移到相应的后面
        }
        for(i=position,j=1;i<position+T[0];i++,j++){
            S[i]=T[j];
        }
        S[0]=S[0]+T[0];
        return TRUE;
    }
    else
    {
        for(i=MAXSIZE;i>=position;i--){
            S[i]=S[i-T[0]]; //i-T[0]到还可以显出的位置，从这个位置开始往前回溯填充到尾部不断往回填
                            //至于填充了那些插入以后无法显出的字符没关系，后面会赋予插入的值，主要是留下可以显出的
        }
        for(i=position,j=1;i<position+T[0];i++,j++){
            S[i]=T[j];
        }
        S[0]=MAXSIZE;
        return FALSE;
    }
}


//在主串S中删除从第position个字符起长度为len的字符串
status StrDelte(string S,int position,int len)
{
    if(position>S[0]||position>S[0]-len+1||len<0)
        return ERROR;
    for(int i=position+len;i<=S[0];i++){
        S[i-len]=S[i];
    }    
    S[0]-=len;
    return OK;
}


//用V替换在主串S中与子串T相等的所有不重叠的串、
status StrReplace(string S,string T,string V)
{
    int i=1; //从第一个字符开始
    if(StrEmptyJudge(T)) //空串
        return ERROR;
    do
    {
        i=Index1(S,T,i);
        if(i){
            StrDelte(S,i,StrLen(T));
            StrInsert(S,V,i);
            i+=StrLen(V);
        }
    } while (i);
    return OK;
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
    string S1,S2,T;
    status dev;
    char ch;
    int i,j;

    //生成一个abcd串
    dev=CreatEqualStr(S1,"abcd");
    if(!dev){
        printf("this string is overflow\n");
        exit(0);
    }
    printf("the len of S1 is %d.\n",StrLen(S1));

    // //用S1复制到S2，打印S2，验证S1的值
    // StrCopy(S2,S1);
    // printf("S2 is:\n");
    // ShowStr(S2);
    ShowStr(S1);

    //生成一个新串efghijk
    dev=CreatEqualStr(S2,"efghijk");
    if(!dev){
        printf("this string is overflow\n");
        exit(0);
    }

    //比较S1和S2的大小
    dev=StrCompare(S1,S2);
    if(dev<0)
        ch='<';
        else if(dev==0)
            ch='=';
            else
                ch='>';
    printf("S1 is %c S2\n",ch);

    //连接S1和S2
    dev=StrConcat(T,S1,S2);
    printf("T is:\n");
    ShowStr(T);
    if(dev==ERROR)
        printf("T is broken\n");

    //清空字符串S1
    ClearStr(S1);
    printf("S1:");
    ShowStr(S1);
    dev=StrEmptyJudge(S1);
    if(dev){
        printf("S1 is empty\n");
        printf("the len of S1 is %d\n",StrLen(S1));
    }

    //在T串中第2个字符开始抽取长度为3的字符串
    dev=SubStr(S2,T,2,3);
    if(dev){
        printf("after get from T,S2 is:\n");
        ShowStr(S2);
    }

    //在串T中删除从第四个字符开始长度为2的字符串
    StrDelte(T,4,2);
    printf("after delte,T is:\n");
    ShowStr(T);

    //在串2第一个字符之前插入T
    dev=StrLen(S2)/2;
    StrInsert(S2,T,dev);
    ShowStr(S2);

    // printf("now T is:\n");
    // ShowStr(T);
    dev=Index1(S2,T,1);
    printf("from %dth positon,T is as the same as S2\n",dev);
    SubStr(T,S2,1,1);
    ShowStr(T);
    //两个串T相连
    StrConcat(S1,T,T);
    ShowStr(S1);

    //取代
    StrReplace(S2,T,S1);
    ShowStr(S2);

    return 0;
}
