/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:14:52 by melaena           #+#    #+#             */
/*   Updated: 2021/09/05 20:07:34 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_change(char **from, char *to)
{
	char	*temp;

	temp = *from;
	*from = to;
	free(temp);
	return (0);
}

int	ft_squeeze(char *str, int i)
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

char	*str_replace(char *str, char *replace, char *to, int start)
{
	char	*new;
	int		i;
	int		len;
	int		j;

	len = ft_strlen(str) + ft_strlen(to) - ft_strlen(replace);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	i = -1;
	while (++i < start)
		new[i] = str[i];
	while (*to)
		new[i++] = *to++;
	j = start + ft_strlen(replace);
	while (i < len)
		new[i++] = str[j++];
	return (new);
}

static char	*str_replace_qmark_var(char *str, int i, int *len)
{
	char	*temp;
	char	*exit_status;

	exit_status = ft_itoa(g_mshell->exit_status);
	temp = str_replace(str, "?", exit_status, i + 1);
	*len = ft_strlen(exit_status);
	return (temp);
}

char	*process_envvar(char *str, int *i)
{
	int		len;
	char	*var;
	char	*temp;
	char	*value;

	len = 0;
	while (ft_isenvkey(str[*i + 1 + len]))
		len++;
	var = ft_substr(str, *i + 1, len);
	value = dict_get_value(g_mshell->env, var);
	len = 0;
	if (value)
	{
		temp = str_replace(str, var, value, *i + 1);
		len = ft_strlen(value);
	}
	else if (!value && str[*i + 1] == '?')
		temp = str_replace_qmark_var(str, *i, &len);
	else
		temp = str_replace(str, var, "", *i + 1);
	ft_squeeze(temp, *i);
	free(var);
	*i += len - 1;
	return (temp);
}
