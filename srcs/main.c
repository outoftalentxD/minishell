/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/08/28 17:41:56 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*g_env;

int	main(int argc, char **argv, char **env)
{
	char *str;

	// str = ft_strdup("asd$USERasd");
	// str = str_replace(str, "USER", "melaena", 4);
	// printf("str: %s\n", str);

	g_env = init_env(env);
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		preparse(&str);
		printf("mod: %s\n", str);
	}
}