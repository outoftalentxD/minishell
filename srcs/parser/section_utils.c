/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 12:21:43 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 12:39:02 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sect_split_elem_pipe(t_sect *elem, int i)
{
	char	*head;
	char	*mid;
	char	*tail;
	t_sect	*temp;
	
	head = ft_substr(elem->content, 0, i);
	mid = ft_strdup()
}