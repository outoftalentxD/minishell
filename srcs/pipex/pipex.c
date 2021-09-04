#include "minishell.h"

t_sect *search_prev_cmd(t_sect *elem)
{
	t_sect *temp;

	temp = elem;
	while(temp)
	{
		if (temp->prev->type == SECT_TYPE_CMD)
			return (temp->prev);
	}
	return (NULL);
}

void child1_process(int *fd, t_sect *elem)
{
	char **args;
	dup2(fd[1], 1);
	close(fd[0]);
	args = sect_form_args(search_prev_cmd(elem));
	exec_command(args);
	exit(EXIT_FAILURE);
}

void child2_process(int *fd, t_sect *elem)
{
	char **args;

	dup2(fd[0], 0);
	close(fd[1]);
	args = sect_form_args(elem->next);
	exec_command(args);
	exit(EXIT_FAILURE);
}

void pipex(t_sect *elem)
{
	int fd[2];
	pid_t child1;
	pid_t child2;
	int status;

	pipe(fd);
	status = 0;
	child1 = fork();
	if (child1 == 0)
		child1_process(fd, elem);
	child2 = fork();
	if (child2 == 0)
		child2_process(fd, elem);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}