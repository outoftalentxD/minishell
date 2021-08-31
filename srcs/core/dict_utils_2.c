/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:26:16 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 16:03:21 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dict_free_elem(t_dict *elem)
{
	free(elem->key);
	free(elem->value);
	free(elem);
	return (0);
}

int	dict_del_elem(t_dict **dict, t_dict *elem)
{
	t_dict	*prev;
	t_dict	*next;

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
		*dict = next;
	}
	else if (!next && prev)
		prev->next = 0;
	else
		*dict = 0;
	dict_free_elem(elem);	
}

int	dict_del_by_key(t_dict **dict, char *key)
{
	t_dict	*elem;
	t_dict	*prev;
	t_dict	*next;

	elem = dict_get_elem(*dict, key);
	if (!elem)
		return (1);
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
		*dict = next;
	}
	else if (!next && prev)
		prev->next = 0;
	else
		*dict = 0;
	dict_free_elem(elem);
}
