/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:28:04 by melaena           #+#    #+#             */
/*   Updated: 2021/08/28 03:06:22 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_squeeze(char *str, int i)
{
	int	len;

	len = ft_strlen(str);
	while (i < len)
	{
		str[i] = str[i + 1];
		i++;
	}
	return (0);
}

int	process_squote(char *str, int i)
{
	int	len;
	int	offset;
	int flag;
	
	flag = 1;
	offset = 1;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i + 1] == '\'')
		{
			offset += flag;
			flag = 0;
		}
		str[i] = str[i + offset];
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("Bad sequence of single quotes\n", STDERR_FILENO);
	return (0);
}

int process_envvar(char *str, int i)
{
	int		len;
	char	*var;
	int		j;
	
	j = i + 1;
	len = 0;
	while (ft_isalnum(str[j]) || str[j] == '_')
	{
		j++;
		len++;
	}
	var = ft_substr(str, i + 1, len);
	printf("var: %s\n", var);
	return (0);
}

int process_dquotes(char *str, int i)
{
	return (0);
}
int	preparse(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			process_squote(str, i);
			i--;
		}
		if (str[i] == '\\')
			ft_squeeze(str, i);
		if (str[i] == '"')
		{
			process_dquotes(str, i);
		}
		if (str[i] == '$')
		{
			process_envvar(str, i);
		}
	}

	return (0);
}