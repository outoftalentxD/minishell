/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:14:36 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 19:23:28 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_apply_env_dquotes(char *str, int *start, int *end)
{
	int		i;
	int		diff;
	char	*temp;

	i = *start - 1;
	while (++i < *end)
	{
		if (str[i] == '$')
		{
			temp = str;
			str = process_envvar(str, &i);
			free(temp);
			*end = i;
			while (str[*end] && str[*end] != '\"')
				(*end)++;
		}
	}
	*end = i;
	return (str);
}

int	process_dquote(char **strs, int *i)
{
	int		j;
	char	*str;
	char	*temp;

	str = *strs;
	j = *i + 1;
	while (str[j] != '\"')
	{
		if (!str[j])
		{
			ft_putstr_fd("Bad sequence of double quotes\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		j++;
	}
	temp = str_apply_env_dquotes(str, i, &j);
	ft_squeeze(temp, j);
	ft_squeeze(temp, *i);
	*strs = temp;
	*i = j - 2;
	return (EXIT_SUCCESS);
}

int	process_squote(char *str, int *i)
{
	int	j;

	j = *i;
	ft_squeeze(str, j);
	while (str[j])
	{
		if (str[j] == '\'')
		{
			ft_squeeze(str, j);
			*i = j - 1;
			return (EXIT_SUCCESS);
		}
		j++;
	}
	ft_putstr_fd("Bad sequence of single quotes\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
