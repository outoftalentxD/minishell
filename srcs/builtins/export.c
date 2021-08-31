/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:36:49 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 02:53:55 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int bi_export(char **args, t_dict *env)
{
	char	**var;
	int		size;
	char	*key;
	char	*value;

	size = get_args_size(args);
	if (size == 1)
		bi_env(env);
	else if (size > 1)
	{
		var = ft_split(args[1], '=');
		key = ft_strdup(var[0]);
		if (var[1])
			value = ft_strdup(var[1]);
		else
			value = ft_strdup("");
		free(var[0]);
		free(var[1]);
		free(var);
		dict_add_elem(&env, dict_init_elem(key, value));
	}
	return (0);
}