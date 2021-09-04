/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/04 18:58:21 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_sect	*elem;
	char	**args;

	g_mshell = init_mshell(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
		elem = parse(line);
		args = sect_form_args(elem);
		exec_command(args);
		while(elem)
		{
			if (elem->type == SECT_TYPE_PIPE)
				pipex(elem);
			elem = elem->next;
		}
		//args = sect_form_args(elem);
		//exec_command(args);

	}
}
