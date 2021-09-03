/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:21:43 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 21:07:06 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**sect_form_args(t_sect *sect)
{
	char	**args;
	int		size;
	t_sect	*elem;
	int		i;

	elem = sect;
	size = 0;
	while (elem && !sect_type_is_pipe(elem))
	{
		if (elem->type == SECT_TYPE_ARG || elem->type == SECT_TYPE_CMD)
			size++;
		elem = elem->next;
	}
	args = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	args[size] = 0;
	while (i < size && sect)
	{
		if (sect->type == SECT_TYPE_ARG || sect->type == SECT_TYPE_CMD)
			args[i++] = sect->content;
		sect = sect->next;
	}
	return (args);
}
