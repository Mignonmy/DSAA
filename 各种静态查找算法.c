#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

//顺序查找算法 
//a为数组，n为数组元素个数,key为查找关键词
int SequentialSearch1(int *a,int n,int key)
{
    for(int i=0;i<=n;i++)
    {
        if(a[i]==key)
        {
            return i;
        }
    }
    return 0;
}

//顺序查找算法优化
int SequentialSearch2(int *a,int n,int key)
{
    a[0]=key;
    int i=n;
    while(a[i]!=key)
    {
        i--;
    }
    return i;
}

//折半查找，前提是数组有序
int BinarySearch(int *a,int n,int key)
{
    int left,right,mid;
    left=1;
    right=n;
    while(left<=right)
    {
        mid=(left+right)/2; //折半
        if(key<a[mid])
        {
            right=mid-1; //-1剔除a[mid]本身
        }
        else if(key>a[mid])
        {
            left=mid+1;
        }
        else
        {
            return mid;
        }
    }
    return 0;
}

//插值查找算法
int InterpolationSearch(int *a,int n,int key)
{
    int left,right,mid;
    left=1;
    right=n;
    while(left<=right)
    {
        mid=left+(right-left)*(key-a[left])/(a[right]-a[left]);
        if(key<a[mid])
        {
            right=mid-1; //-1剔除a[mid]本身
        }
        else if(key>a[mid])
        {
            left=mid+1;
        }
        else
        {
            return mid;
        }
    }
    return 0;
}

//斐波那契查找
int Fibonacci_Search(int *a,int n,int key)
{
    int left,right,mid,i,k;
    int F[20];
    left=1;
    right=n;
    k=0;

    //斐波那契数列
    F[0]=0;
	F[1]=1;
	for(i = 2;i < 22;i++)  
	{ 
		F[i] = F[i-1] + F[i-2];  
	} 

    //寻找大概相近合适的所需斐波那契数列数字
    while(n>F[k]-1){
        k++;
    }

    //修正数组个数到所选的斐波那契数
    for(i=n;i<F[k]-1;i++)
    {
        a[i]=a[n];
    }

    //按照黄金分割个数查找
    while(left<=right)
    {
        mid=left+F[k-1]-1;
        if(key<a[mid])
        {
            right=mid-1;
            k=k-1;
        }
        else if(key>a[mid])
        {
            left=mid+1;
            k=k-2;
        }
        else
        {
            if(mid<=n)
                return mid;
            else
                return n;
        }
    }

    return 0;
}


//下面用main函数验证
int main()
{
    int a[MAXSIZE+1],i,result;
	int arr[MAXSIZE]={0,1,16,24,35,47,59,62,73,88,99};
		
	for(i=0;i<=MAXSIZE;i++)
	{
		a[i]=i;
	}
	result=SequentialSearch1(a,MAXSIZE,MAXSIZE);
	printf("SequentialSearch1:%d \n",result);
	result=SequentialSearch2(a,MAXSIZE,1);
	printf("SequentialSearch2:%d \n",result);

	result=BinarySearch(arr,10,62);
	printf("BinarySearch:%d \n",result);

	
	result=InterpolationSearch(arr,10,62);
	printf("InterpolationSearch:%d \n",result);

	result=Fibonacci_Search(arr,10,62);
	printf("Fibonacci_Search:%d \n",result);

    return 0;
}