/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:55:02 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

int	main(int argc, char **argv, char **envp)
{
	t_sect	*elem;

	(void)argc;
	(void)argv;
	g_mshell = init_mshell(envp);
	while (1)
	{
		set_signal_handlers();
		elem = parser();
		if (!elem)
			continue ;
		if (input_is_valid(elem))
		{
			free_sect(elem);
			continue ;
		}
		update_mshell_env();
		cmd_execution(elem);
		free_sect(elem);
	}
	return (EXIT_SUCCESS);
}
