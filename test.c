#include <stdio.h>
// Shared variable
int shared_variable = 0;
// Busy wait solution
void busy_wait()
{
    while (shared_variable != 1);
}
// Function to read the shared variable
void read_shared_variable()
{
    printf("Reading shared variable: %d\n", shared_variable);
}
// Function to write the shared variable
void write_shared_variable()
{
    printf("Writing shared variable\n");
    shared_variable = 1;
}
int main()
{
    // Read the shared variable
    read_shared_variable();
    // Write the shared variable
    write_shared_variable();
    // Use busy wait to ensure the shared variable is updated
    busy_wait();
    // Print the final value of the shared variable
    printf("Final shared variable: %d\n", shared_variable);
    return 0;
}

