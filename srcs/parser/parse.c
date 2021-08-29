/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:28:04 by melaena           #+#    #+#             */
/*   Updated: 2021/08/29 12:24:24 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparse(char **strs)
{
	int		i;
	char	*str;
	char	*temp;

	str = *strs;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (process_squote(str, &i))
				return (-1);
		}
		else if (str[i] == '\\')
			ft_squeeze(str, i);
		else if (str[i] == '"')
		{
			if (process_dquote(&str, &i))
				return (-1);
		}
		else if (str[i] == '$')
			str_change(&str, process_envvar(str, &i));
		*strs = str;
	}
	return (0);
}
