#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	while(1)
	{
		write(1, "$ ", 2);
		char line[128][256];
		char* line2[128];
		char word[256];
		int lineI = 0;
		int wordI = 0;
		char curr[4];
		bool newLine = false;
		bool secondSpace = false;
		while(!newLine && (read(0, curr, 1) > 0))
		{
			if(curr[0] == ' ')
			{
				if(!secondSpace)
				{
					word[wordI] = '\0';
					wordI = 0;
					strcpy(line[lineI++], word);
					secondSpace = true;
				}
			}
			else if(curr[0] == '\n')
			{
				word[wordI] = '\0';
				wordI = 0;
				strcpy(line[lineI++], word);
				newLine = true;
				secondSpace = false;
			}
			else
			{
				word[wordI++] = curr[0];
				secondSpace = false;
			}
		}
		if(strcmp(line[0], "exit") == 0 || strcmp(line[0], "quit") == 0)
		{
			exit(0);
		}
		else
		{
			if(fork() == 0)
			{
				int i;
				for(i = 0; i < lineI; i++)
				{
					line2[i] = line[i];
				}
				line2[lineI] = NULL;
				execvp(line2[0], line2);
				write(1, "wrong command\n", 14);
				exit(-1);
			}
			else
			{
				wait(0);
			}
		}
	}
}
