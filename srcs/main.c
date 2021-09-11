/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 14:31:32 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

void	print_sections(t_sect *elem)
{
	char	*content;
	
	while (elem)
	{
		if (!elem->content)
			content = "NULL";
		else
			content = elem->content;
		printf("content: |%s| type %d cmdtype %d\n", content, elem->type, elem->cmd_type);
		elem = elem->next;
	}
}

int	postparse(t_sect **sect)
{
	t_sect	*elem;
	t_sect	*temp;

	elem = *sect;
	while (elem)
	{
		if (!elem->content[0])
		{
			free(elem->content);
			elem->content = NULL;
			if (elem->type == SECT_TYPE_CMD)
			{
				sect_set_type(elem, SECT_TYPE_NULL);
				if (elem->next && elem->next->type == SECT_TYPE_ARG)
					sect_set_type(elem->next, SECT_TYPE_CMD);
			}
			else
				sect_set_type(elem, SECT_TYPE_NULL);
		}
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
		postparse(&elem);
		// g_mshell->sect = elem;
		if (input_is_valid(elem))
			continue ;
		// print_sections(elem);
		cmd_execution(elem);
		unlink(".heredoc");
		// free_sect(elem);
	}
	// free_mshell();
	return (EXIT_SUCCESS);
}
