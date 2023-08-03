#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
void firstfit(int blockSize[], int processSize[], int m, int n)
{
    for(int i=0;i<n;i++)
    {
        int alot=0;
        for(int j=0;j<m;j++)
        {
            if(blockSize[j]>=processSize[i])
            {
                blockSize[j]-=processSize[i];
                printf("%d\t\t%d\t%d\n",i+1,processSize[i],j+1);
                alot=1;
                break;
            }
        }
        if(!alot)
        {
            printf("%d\t\t%d\tNot allocated\n",i+1,processSize[i]);
        }
    }
}
int main(){
    int blockSize[] = {300, 50, 200, 350, 70};
    int processSize[] = {200, 47, 212, 426, 10};
    int m=sizeof(blockSize)/sizeof(blockSize[0]);
    int n=sizeof(processSize)/sizeof(processSize[0]);
    printf("Process\tProcess_Size\tBlock no\n");
    firstfit(blockSize,processSize,m,n);

return 0;
}
