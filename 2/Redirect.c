#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    char output_path[100], input_argument[100], input_program[100];
    printf("path of input program:");
    scanf("%s", input_program);
    printf("path of output text:");
    scanf("%s", output_path);
    printf("path of input arguments:");
    scanf("%s", input_argument);
    printf("pid:%d\n", getpid());
    
    int frk = 0;
    if (frk < 0)
    {
        printf("unfortunately fork failed!");
        return 0;
    }

    else if (frk == 0)
    {
        printf("child pid is: %d\n", getpid());
        
        FILE *open_program;
        open_program = popen(input_program, "r");
        if (open_program == NULL)
        {
            printf("Given file is not executable!");
            return 0;
        }
        
        FILE *output_file;
        output_file = fopen(output_path, "w");
        if (output_file == NULL)
        {
            printf("it should be a text file!");
            return 0;
        }
        
        char p[1035];
        while (fgets(p, sizeof(p), open_program) != NULL)
        {
            fprintf(output_file, "%s", p);
        }
        fclose(output_file);
        pclose(open_program);
        return 0;
    }

    else
    {
        int w = wait(NULL);
        printf("Parent of %d is: %d", frk, getpid());
        return 0;
    }
}