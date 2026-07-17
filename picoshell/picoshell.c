#include <unistd.h>
#include <stdio.h>

int    picoshell(char **cmds[])
{
	if (!cmds || !*cmds)
		return (1);
	int fd[2];
	int pid = 0;
	int i = 0;
	int	oldfd = 0;
	int status;

	pipe(fd);
	while (cmds[i] != NULL)
	{
		i++;
	}
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
