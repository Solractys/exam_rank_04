#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pipe(fd);
	if (fork() == 0)
	{
				if (type == 'r')
					dup2(fd[1], STDOUT_FILENO);
				else if (type == 'w')
					dup2(fd[0], STDIN_FILENO);
				close(fd[1]);
				close(fd[0]);
		execvp(file, argv);
	}
	if (type == 'r')
	{
		close (fd[1]);
		return (fd[0]);
	}
	else if (type == 'w')
	{
		close (fd[0]);
		return (fd[1]);
	}
	else
		return (-1);
	close (fd[1]);
	close (fd[0]);
}

char	*get_next_line(int fd)
{
	char *buffer = malloc(9999 * sizeof(char));
	read(fd, buffer, 9999);
	return (buffer);
}

void	ft_putstr(char *str)
{
	int i = 0;
	while (str && str[i])
		write (1, &str[i++], 1);
}

int	main(void)
{
	int fd = ft_popen("ls", (char *const[]){"ls",  "|", "grep", "ft_*",  NULL}, 'r');
	char *line = get_next_line(fd);
	ft_putstr(line);
	return (0);
}
