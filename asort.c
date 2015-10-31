// This file contains an attempt at the bonus points
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int i;
    char outputBuffer[4096];
    int outputBufferLen = 0;

    // Checks argment length. If only one, then quit the program with an error message.
    if(argc == 1)
    {
        outputBufferLen = sprintf(outputBuffer, "There are no arguments included, this program needs at least one argument to run\n");
        write(1, outputBuffer, outputBufferLen);
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
                outputBufferLen = sprintf(outputBuffer, "Access Denied on Directory Creation, exiting \n");
                write(1, outputBuffer, outputBufferLen);
            default:
                exit(0); 
        }
    }

    for(i = 1; i < argc; i++)
    {
        int forkReturnValue = fork(); 
        int execReturnValue = 0;

        //Only child process runs this    
        if(forkReturnValue == 0) {
            int fd;
            char * envp[] = { NULL };
            char * args[] = { NULL, NULL, NULL }; 
            char * output[] = { NULL };
       
            //Malloc memory for strings 
            args[0] = malloc(sizeof("/usr/bin/sort "));
            args[1] = malloc(sizeof(argv[i]));
            output[0] = malloc(sizeof("SORTED/") + sizeof(argv[i]));

            if(args[0] == NULL || args[1] == NULL || output[0] == NULL)
            {
                outputBufferLen = sprintf(outputBuffer, "Malloc failed, exiting");
                write(1, outputBuffer, outputBufferLen);
                exit(0);
            }   

            //Copy strings into memory designed for it.
            strcpy(args[0], "/usr/bin/sort ");
            strcpy(args[1], argv[i]);

            strcpy(output[0], "SORTED/");
            strcat(output[0], argv[i]);

            //Checks to see if the file exists in the main directoy
            if((fd = open(argv[i], O_RDWR)) != -1)
            {
                //Close the file to preserve the space, and overwrite the variable
                close(fd);
                       
                //Open the file descriptor for the output file, and bind it to sdtout using dup2
                if((fd = open(*output, O_CREAT | O_RDWR | O_TRUNC)) == 0)
                {
                    outputBufferLen = sprintf(outputBuffer, "Opening output file failed, exiting\n");
                    write(1, outputBuffer, outputBufferLen);
                    exit(0);
                }
    
                dup2(fd, 1);
                close(fd);
            }
                
            //Create new process for sort, return the error if needed
            return execve("/usr/bin/sort", args, envp );

        }

        //wait for child prcesses to finish
        wait(&execReturnValue);
        
        //print if the file was sorted correctly
        if(execReturnValue == 0)
        {
            outputBufferLen = sprintf(outputBuffer, "%s : success (0)\n", argv[i]);
            write(1, outputBuffer, outputBufferLen);
        }
    }

    //Print that we are done
    outputBufferLen = sprintf(outputBuffer, "All done!\n");
    write(1, outputBuffer, outputBufferLen);
    
    return(0);
}
