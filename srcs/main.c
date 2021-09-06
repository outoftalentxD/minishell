/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/06 23:06:49 by melaena          ###   ########.fr       */
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

static int close_prev_fd(t_sect *elem)
{
	elem = elem->prev;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
		{
			if (elem->fd->in != STDIN_FILENO)
				close(elem->fd->in);
			if (elem->fd->out != STDOUT_FILENO)
				close(elem->fd->out);
			return (EXIT_FAILURE);
		}
		elem = elem->prev;
	}
	return (1);
}


void child_process(t_sect *elem)
{
	char **args;

	dup2(elem->fd->in, 0);
	dup2(elem->fd->out, 1);
	close_prev_fd(elem);
	args = sect_form_args(elem);
	exec_command(args);
	exit(EXIT_FAILURE);
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
				child = fork();
				if (child == 0)
					child_process(elem);
				// waitpid(child, &status, 0);
				// close_pipeline(elem);
				// close(elem->fd->in);
				// close(elem->fd->out);
			}
			elem = elem->next;
		}
		elem = temp;
		while (elem)
		{
			if (elem->type == SECT_TYPE_CMD)
				waitpid(-1, &status, 0);
			elem = elem->next;
		}
		close_pipeline(temp);
		print_sections(temp);
	}
}