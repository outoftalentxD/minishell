/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/06 21:36:32 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

int set_signal_handlers()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void child_process(t_sect *elem)
{
	char **args;
	pid_t child;
	int status;

	status = 0;
	child = fork();
	if (child == 0)
	{
		// printf("cmd: %s\n fd %d\n", elem->content, elem->fd->out);
		dup2(elem->fd->in, 0);
		dup2(elem->fd->out, 1);
	//execlp("usr/bin/wc", "usr/bin/wc", NULL);
		args = sect_form_args(elem);
		exec_command(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(-1, &status, 0);
		write(1, " 1st FINISHED BTW\n", 19);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_sect	*elem;
	t_sect	*temp;
	char	**args;
	int status;
	pid_t child;

	g_mshell = init_mshell(env);
	while (1)
	{
		set_signal_handlers();
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
		elem = parse(line);
		if (!elem)
			continue;
		// print_sections(elem);
		
		temp = elem;
		while (elem)
		{
			if (elem->type == SECT_TYPE_CMD)
				open_pipeline(elem);
			elem = elem->next;
		}
		elem = temp;
		status = 0;
		while (elem)
		{
			if (elem->type == SECT_TYPE_CMD)
			{
				child_process(elem);
			}
			elem = elem->next;
		}
		
		// while(elem)
		// {
		// 	// if (elem->type == SECT_TYPE_CMD)
		// 	// {
		// 		if (elem->type == SECT_TYPE_PIPE)
		// 			pipex(elem);
		// 	// }
		// 	elem = elem->next;
		// }
	}
}

			// if (elem->type == SECT_TYPE_CMD)
			// {
			// 	if (elem->cmd_type == SECT_CMD_TYPE_PIPE)
			// 	{
			// 		int fd[2];
			// 		pipe(fd);
			// 		dup2(fd[1], g_mshell->fd->out);
			// 		g_mshell->fd->out = fd[1];
			// 		g_mshell->fd->in = fd[0];
			// 		//fork exec;
			// 		dup2(fd[0], 0);
			// 	}
			// 		pipex(elem);
			// 	else
			// 	{
			// 		args = sect_form_args(elem);
			// 		exec_command(args);
			// 	}
			// }