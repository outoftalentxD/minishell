/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/06 19:54:30 by kbulwer          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_sect	*elem;
	char	**args;

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
		// args = sect_form_args(elem);
		// exec_command(args);
		while(elem)
		{
			// if (elem->type == SECT_TYPE_CMD)
			// {
				if (elem->type == SECT_TYPE_PIPE)
					pipex(elem);
			// }
			elem = elem->next;
		}
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