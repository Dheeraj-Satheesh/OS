#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
void worstfit(int blockSize[], int processSize[], int m, int n)
{
    for(int i=0;i<n;i++)
    {
        int index=-1;
        int max=-10;
        for(int j=0;j<m;j++)
        {
            int temp=blockSize[j]-processSize[i];
            if(temp>=0 && temp>max)
            {
                max=temp;
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
    int blockSize[] = {5, 4, 3, 6, 7};
    int processSize[] ={1, 3, 5, 3};
    int m=sizeof(blockSize)/sizeof(blockSize[0]);
    int n=sizeof(processSize)/sizeof(processSize[0]);
    printf("Process\tProcess_Size\tBlock no\n");
    worstfit(blockSize,processSize,m,n);

return 0;
}
