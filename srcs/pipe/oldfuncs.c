/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:36:28 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 13:36:40 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_out_rdrct(t_sect *elem)
{
	while (elem)
	{
		if (!elem->next)
			return (EXIT_FAILURE);
		if (elem->type == SECT_TYPE_OUT)
			dup_out_rdrct(elem, SECT_TYPE_OUT);
		else if (elem->type == SECT_TYPE_OUT_AP)
			dup_out_rdrct(elem, SECT_TYPE_OUT_AP);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

int	process_in_rdrct(t_sect *elem)
{
	int	code;

	code = 0;
	while (elem)
	{
		if (!elem->next)
			return (EXIT_FAILURE);
		if (elem->type == SECT_TYPE_IN)
			code = dup_in_rdrct(elem, SECT_TYPE_IN);
		else if (elem->type == SECT_TYPE_IN_DLM)
			code = dup_in_rdrct(elem, SECT_TYPE_IN_DLM);
		if (code)
			return (EXIT_FAILURE);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}
