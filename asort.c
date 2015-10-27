#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    int i;

    if(argc == 1)
    {
        printf("There are no arguments included, this program needs at least one argument to run.\n");
    }

    for(i = 1; i < argc; i++)
    {
        printf("These are the arguments for arg %d, %s\n", i, argv[i]);
    }

    return(0);
}
