#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
int find(int queue[],int head,int n, int direction)
{
    int size=n;
    int temp[size];
    int head_index;
    for (int i = 0; i < size; i++)
    {
        temp[i]=abs(queue[i]-head);
    }
    int min=temp[0];
    for(int i=0;i<size;i++)
    {
         if(direction)//right direction
        {
            if(queue[i]>head)
            {
                if(temp[i]<min)
                {
                    min=temp[i];
                    head_index=i;
                }
            }
        }
        else{//left direction
            if(queue[i]<head)
            {
                if(temp[i]<min)
                {
                    min=temp[i];
                    head_index=i;
                }
            }
        }
    }
    return head_index;
}
int  scan(int queue[],int direction, int head, int n)
{

    int index=find(queue,head,n,direction);
    int temp[n];
    int total_st=0,i=0,j=0;
    if(direction==1)//right side rotation
    {
        for(i=index;i<n;i++)
        {
            temp[j++]=queue[i];
        }
        for(i=0;i<index;i++)
        {
            temp[j++]=queue[i];
        }

    }
    else//left side rotation
    {
       for(i=index;i>=0;i--)
        {
            temp[j++]=queue[i];
        } 
        for(i=n-1;i>index;i--)
        {
            temp[j++]=queue[i];
        }
    }
    for (int i = 0; i < n; i++) {
        total_st += abs(head - temp[i]);
        head = temp[i];
    }
    return total_st;  
}
int main() {
    int queue[1000], head, n, total_seek = 0;
    int direction;
    printf("Enter the size of the disk queue: ");
    scanf("%d", &n);
    printf("Enter the disk queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);
    // Sort the queue in ascending order
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (queue[j] > queue[j + 1]) {
                   swap(&queue[j], &queue[j+1]);
                }
            }
        }
    total_seek=scan(queue,direction,head,n);
    printf("Total Seek Time: %d\n", total_seek);
    return 0;
}