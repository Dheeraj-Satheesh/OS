#include <stdio.h>  
#include <stdlib.h>    
  
int main()  
{  
    int num, n;
    printf (" Enter a number to display the absolute value: ");  
    scanf ("%d", &num); 
    n = abs (num);  
      
    printf ("\n The absolute value of %d is %d. ", num, n);  
    return 0;  
}  