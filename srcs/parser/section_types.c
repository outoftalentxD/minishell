/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:18:31 by melaena           #+#    #+#             */
/*   Updated: 2021/09/08 17:17:58 by melaena          ###   ########.fr       */
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

static int	set_cmd_type(t_sect *sect)
{
	t_sect	*elem;

	elem = sect;
	while (elem)
	{
		if (elem->type == SECT_TYPE_PIPE)
		{
			sect->cmd_type = SECT_CMD_TYPE_PIPE;
			return (EXIT_SUCCESS);
		}
		else if (elem->type == SECT_TYPE_IN
			|| elem->type == SECT_TYPE_OUT
			|| elem->type == SECT_TYPE_IN_DLM
			|| elem->type == SECT_TYPE_OUT_AP)
		{
			sect->cmd_type = SECT_CMD_TYPE_RDRCT;
			return (EXIT_SUCCESS);
		}
		elem = elem->next;
	}
	sect->cmd_type = SECT_CMD_TYPE_END;
	return (EXIT_SUCCESS);
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
	else if (!sect->prev || sect->prev->type == SECT_TYPE_PIPE)
		sect->type = SECT_TYPE_CMD;
	else
		sect->type = SECT_TYPE_ARG;
	return (0);
}

int	sect_set_type_to_all(t_sect *sect)
{
	t_sect	*temp;

	temp = sect;
	while (sect)
	{
		sect_set_type(sect);
		sect = sect->next;
	}
	sect = temp;
	while (sect)
	{
		if (sect->type == SECT_TYPE_CMD)
			set_cmd_type(sect);
		else if (sect->type == SECT_TYPE_OUT)
			sect->next->cmd_type = SECT_TYPE_OUT;
		else if (sect->type == SECT_TYPE_OUT_AP)
			sect->next->cmd_type = SECT_TYPE_OUT_AP;
		else if (sect->type == SECT_TYPE_IN)
			sect->next->cmd_type = SECT_TYPE_IN;
		else if (sect->type == SECT_TYPE_IN_DLM)
			sect->next->cmd_type = SECT_TYPE_IN_DLM;
		sect = sect->next;
	}
	return (EXIT_SUCCESS);
}
