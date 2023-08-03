#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
void bestfit(int blockSize[], int processSize[], int m, int n)
{
    for(int i=0;i<n;i++)
    {
        int index=-1;
        int min=__INT_MAX__;
        for(int j=0;j<m;j++)
        {
            int temp=blockSize[j]-processSize[i];
            if( temp >=0 && temp<min)
            {
                min=temp;
                index=j;
            }
        }
        if(index==-1)
        {
            printf("%d\t%d\tNot allocated\n",i+1,processSize[i]);
        }
        else{
            blockSize[index]-=processSize[i];
            printf("%d\t%d\t%d\n",i+1,processSize[i],index+1);
        }
    }
}
int main(){
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m=sizeof(blockSize)/sizeof(blockSize[0]);
    int n=sizeof(processSize)/sizeof(processSize[0]);
    printf("Process\tP_Size\tBlock no\n");
    bestfit(blockSize,processSize,m,n);

return 0;
}
