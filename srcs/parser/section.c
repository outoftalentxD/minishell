/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:20:19 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 12:35:07 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sect	*sect_init_elem(char *content)
{
	t_sect	*elem;

	elem = ft_calloc(1, sizeof(t_sect));
	if (!elem)
		return (0);
	elem->content = content;
	elem->type = 0;
	elem->next = 0;
	elem->prev = 0;
	return (elem);
}

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

int	sect_split_elem(t_sect **sect)
{
	char	*content;
	t_sect	*elem;
	int		i;

	i = 0;
	elem = *sect;
	content = elem->content;
	while (content[i])
	{
		if (content[i] == '|')
		{
			sect_split_elem_pipe(elem);
			return (0);
		}
		i++;

	}
}

int	process_sections(t_sect **sect)
{
	t_sect	*elem;
	int		i;
	
	elem = *sect;
	if (!elem)
		return (0);
	while (elem)
	{
		sect_split_elem()
		elem = elem->next;
	}

}