#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

//˳������㷨 
//aΪ���飬nΪ����Ԫ�ظ���,keyΪ���ҹؼ���
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

//˳������㷨�Ż�
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

//�۰���ң�ǰ������������
int BinarySearch(int *a,int n,int key)
{
    int left,right,mid;
    left=1;
    right=n;
    while(left<=right)
    {
        mid=(left+right)/2; //�۰�
        if(key<a[mid])
        {
            right=mid-1; //-1�޳�a[mid]����
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

//��ֵ�����㷨
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
            right=mid-1; //-1�޳�a[mid]����
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

//쳲���������
int Fibonacci_Search(int *a,int n,int key)
{
    int left,right,mid,i,k;
    int F[20];
    left=1;
    right=n;
    k=0;

    //쳲���������
    F[0]=0;
	F[1]=1;
	for(i = 2;i < 22;i++)  
	{ 
		F[i] = F[i-1] + F[i-2];  
	} 

    //Ѱ�Ҵ��������ʵ�����쳲�������������
    while(n>F[k]-1){
        k++;
    }

    //���������������ѡ��쳲�������
    for(i=n;i<F[k]-1;i++)
    {
        a[i]=a[n];
    }

    //���ջƽ�ָ��������
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


//������main������֤
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