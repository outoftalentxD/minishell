/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:20:19 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 16:22:36 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sect_add_elem(t_sect **sect, t_sect *elem)
{
	t_sect	*temp;

	temp = *sect;
	if (!temp)
	{
		*sect = elem;
		return (0);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
	elem->prev = temp;
	return (0);
}

int	sect_free_elem(t_sect *elem)
{
	free(elem->content);
	free(elem);
	return (0);
}

int	sect_del_elem(t_sect **sect, t_sect *elem)
{
	t_sect	*prev;
	t_sect	*next;

	prev = elem->prev;
	next = elem->next;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (!prev && next)
	{
		next->prev = 0;
		*sect = next;
	}
	else if (!next && prev)
		prev->next = 0;
	else
		*sect = 0;
	sect_free_elem(elem);
	return (0);
}

t_sect	*sect_sub_elem(char *str, int start, int len)
{
	t_sect	*elem;

	elem = sect_init_elem(ft_substr(str, start, len));
	if (!elem)
		return (0);
	return (elem);
}
