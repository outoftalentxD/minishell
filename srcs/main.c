/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/09 20:28:10 by melaena          ###   ########.fr       */
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
			return (0);
		add_history(line);
		elem = parse(line);
		if (!elem)
			continue ;
		// print_sections(elem);
		// args = sect_form_args(elem);
		// while (*args)
		// 	printf("arg: %s\n", *args++);			
		
		cmd_execution(elem);
		unlink(".heredoc");
	}
	return (EXIT_SUCCESS);
}
