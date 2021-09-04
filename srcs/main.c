/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 02:44:10 by melaena          ###   ########.fr       */
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
		args = sect_form_args(elem);
		exec_command(args);
		// while(elem)
		// {
		// 	if (elem->type == SECT_TYPE_PIPE)
		// 		pipex(elem);
		// 	elem = elem->next;
		// }
	}
}
