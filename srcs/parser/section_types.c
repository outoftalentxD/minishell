/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:18:31 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 20:50:57 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sect_type_is_pipe(t_sect *elem)
{
	if (elem->type == SECT_TYPE_PIPE)
		return (1);
	else
		return (0);
}

int	sect_set_type_to_arg(t_sect *elem)
{
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

int	sect_set_type(t_sect *sect)
{
	if (!ft_strcmp(sect->content, "|"))
		sect->type = SECT_TYPE_PIPE;
	else if (!ft_strcmp(sect->content, ">"))
		sect->type = SECT_TYPE_OUT;
	else if (!ft_strcmp(sect->content, ">>"))
		sect->type = SECT_TYPE_OUT_AP;
	else if (!ft_strcmp(sect->content, "<"))
		sect->type = SECT_TYPE_IN;
	else if (!ft_strcmp(sect->content, "<<"))
		sect->type = SECT_TYPE_IN_DLM;
	else if (!sect->prev || sect_type_is_pipe(sect->prev))
		sect->type = SECT_TYPE_CMD;
	else
		sect->type = SECT_TYPE_ARG;
	return (0);
}

int	sect_set_type_to_all(t_sect *sect)
{
	while (sect)
	{
		sect_set_type(sect);
		sect = sect->next;
	}
	return (0);
}
