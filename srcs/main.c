/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 22:36:27 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

void	print_sections(t_sect *elem)
{
	while (elem)
	{
		printf("content: %s type %d cmdtype %d\n", elem->content, elem->type, elem->cmd_type);
		elem = elem->next;
	}
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
			process_eof();
		add_history(line);
		elem = parse(line);
		g_mshell->sect = elem;
		if (input_is_valid(elem))
			continue ;
		cmd_execution(elem);
		unlink(".heredoc");
		free_sect(elem);
	}
	free_mshell();
	return (EXIT_SUCCESS);
}
