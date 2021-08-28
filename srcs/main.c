/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/08/28 03:53:45 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_dict *denv;


	denv = init_env(env);
	printf("%s\n", dict_get_value(denv, "USER"));
	printf("%s\n", dict_get_value(denv, "GIT_ASKPASS"));
	// while (1)
	// {
	// 	str = readline("minishell$ ");
	// 	add_history(str);
	// 	preparse(str);
	// 	printf("mod: %s\n", str);
	// }
}