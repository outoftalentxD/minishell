/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:13:48 by melaena           #+#    #+#             */
/*   Updated: 2021/08/28 03:46:30 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *dict_get_value(t_dict *dict, char *key)
{
	t_dict *elem;
	
	elem = dict_get_elem(dict, key);
	return (elem->value);
}

t_dict *dict_get_elem(t_dict *dict, char *key)
{
	while (dict->next)
	{
		if (!ft_strcmp(dict->key, key))
			return (dict);
		dict = dict->next;
	}
	return (0);
}

t_dict *dict_init_elem(char *key, char *value)
{
	t_dict *elem;

	elem = ft_calloc(1, sizeof(t_dict));
	if (!elem)
		return (0);
	elem->key = key;
	elem->value = value;
	elem->next = 0;
	return (elem);
}

int	dict_add_elem(t_dict **dict, t_dict *elem)
{
	t_dict *temp;
	
	temp = *dict;
	if (!temp)
	{
		*dict = elem;
		return (0);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
	return (0);

}