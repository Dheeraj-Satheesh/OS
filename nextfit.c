#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

void nextfit(int blockSize[], int processSize[], int m, int n)
{
    int j=0;
    for(int i=0;i<n;i++)
    {
        int alot=0;
        for(;j<m;j++)
        {
            if(blockSize[j]>=processSize[i])
            {
                blockSize[j]-=processSize[i];
                printf("%d\t%d\t%d\n",i+1,processSize[i],j+1);
                alot=1;
                break;
            }
        }
        if(!alot)
        {
            printf("%d\t%d\tNot allocated\n",i+1,processSize[i]);
        }
    }
}
int main(){
    int blockSize[] = {5, 10, 20};
    int processSize[] = {10, 20, 30};
    int m=sizeof(blockSize)/sizeof(blockSize[0]);
    int n=sizeof(processSize)/sizeof(processSize[0]);
    printf("Process\tProcess Size\tBlock no\n");
    nextfit(blockSize,processSize,m,n);
    
return 0;
}