/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:21:43 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 22:38:18 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_to_char(char *str, int start, int set, int *flag)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = start;
	while (str[i])
	{
		sect_set_quotes_flag(str[i], flag);
		if (str[i] == set && !*flag)
		{
			if (i - start == 0 && str[i] == str[i + 1] && str[i] != '|')
				return (-1);
			return (i);
		}
		i++;
	}
	return (len);
}

static int	sect_is_bin_arg(t_sect *elem)
{
	if (elem->type == SECT_TYPE_CMD)
		return (1);
	else if (elem->type == SECT_TYPE_ARG && elem->cmd_type == 0)
		return (1);
	else
		return (0);
}

int	sect_is_specified(t_sect *elem)
{
	if (elem->type == SECT_TYPE_IN_DLM
		|| elem->type == SECT_TYPE_OUT
		|| elem->type == SECT_TYPE_OUT_AP
		|| elem->type == SECT_TYPE_PIPE
		|| elem->type == SECT_TYPE_IN)
		return (1);
	else
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
		i = len_to_char(str, start, *set, &flag);
		if (i == -1)
			return (2);
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
		if (sect_is_bin_arg(elem))
			size++;
		elem = elem->next;
	}
	args = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	args[size] = 0;
	while (i < size && sect)
	{
		if (sect_is_bin_arg(sect))
			args[i++] = sect->content;
		sect = sect->next;
	}
	return (args);
}
