#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int    picoshell(char **cmds[])
{
	int i = 0, pid, status, fd[2], in_fd = 0;
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fd) < 0)
			return (1);
		if ((pid = fork()) < 0)
			return (1);
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close (in_fd);
			}
			if (cmds[i + 1])
			{
				dup2(fd[1], 1);
				close (fd[1]);
				close (fd[0]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (in_fd != 0)
			close (in_fd);
		if (cmds[i + 1])
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		i++;
	}
	while (wait(&status) > 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			return (1);
	}
	return (0);
}


int main(void)
{
    // char *cmd1[] = {"/bin/ls", "level-1", NULL};
    char *cmd1[] = {"/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/grep", "picoshell", NULL};
    char **cmds[] = {cmd1, cmd2, NULL};

    int result = picoshell(cmds);
    printf("picoshell returned %d\n", result);

    return 0;
}
