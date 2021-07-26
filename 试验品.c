#include <stdio.h>
struct node
{
    int num;/* data */
};


void change(struct node a[10])
{
    a[0].num=1002;
}
int main(void)
{
    struct node data[10];
    data[0].num=1001;
    change(data);
    printf("%d",data[0].num);
    return 0;
}
