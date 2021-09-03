/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:21:43 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 17:43:40 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sect	*sect_sub_elem(char *str, int start, int len)
{
	t_sect	*elem;

	elem = sect_init_elem(ft_substr(str, start, len));
	if (!elem)
		return (0);
	return (elem);
}

static int	sect_set_quotes_flag(int c, int *flag)
{
	if (c == '"' && *flag == 0)
		*flag = 'd';
	else if (c == '"' && *flag == 'd')
		*flag = 0;
	else if (c == '\'' && *flag == 0)
		*flag = 's';
	else if (c == '\'' && *flag == 's')
		*flag = 0;
	return (0);
}

int	get_section_len(char *str, int start, char *set)
{
	int	i;
	int	min;
	int	flag;
	int	len;

	flag = 0;
	min = ft_strlen(str) + 1;
	while (*set)
	{
		i = start;
		while (str[i])
		{
			sect_set_quotes_flag(str[i], &flag);
			if (str[i] == *set && !flag)
				break ;
			i++;
		}
		len = i - start;
		if (len < min)
			min = len;
		set++;
	}
	if (min <= 1)
		min = 1;
	return (min);
}
