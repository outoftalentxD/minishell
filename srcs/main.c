/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 15:04:54 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*g_env;

int	main(int argc, char **argv, char **env)
{
	char *line;
	int i;
	char **args;
	
	g_env = init_env(env);
	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		args = ft_split(line, ' ');
		i = 0;
		while (args[i])
		{
			preparse(&args[i]);
			i++;
		}
		exec_command(args);
	}
}