#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char * argv[])
{
    int i;

    // Checks argment length. If only one, then quit the program with an error message.
    if(argc == 1)
    {
        printf("There are no arguments included, this program needs at least one argument to run.\n");
        exit(0);
    }

    //Make directory, with error handlers. If the directory is already there, it does nothing.
    if(mkdir("SORTED", 0700) == -1)
    {
        switch(errno)
        {
            case EEXIST:    //Normal operation for directories that are already created
                break;
            case EACCES:
                printf("Access Denied on Directory Creation\n");
            default:
                exit(0); 
        }
    }

    for(i = 1; i < argc; i++)
    {
        char arg0[12] = " -o SORTED/";
        char * arg1;
        arg1 = malloc(sizeof(char) * (2 * strlen(argv[i]) + strlen(arg0) + 1));
        if(arg1 == NULL)
        {
            printf("malloc failed, exiting");
            exit(0);
        } 

        strcpy(arg1, argv[i]);
        strcat(arg1, arg0);
        strcat(arg1, argv[i]);
        
        printf("These are the arguments for arg %d, %s, and %s\n", i, argv[i], arg0);        
        
        if(fork() == 0) {
            execve("sort", arg1, NULL);
            free(arg1); 
        }

                 
    }


    return(0);
}
