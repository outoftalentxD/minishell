/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:39:45 by melaena           #+#    #+#             */
/*   Updated: 2021/09/06 21:36:24 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sect	*get_next_cmd(t_sect *elem)
{
	elem = elem->next;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			return (elem);
		elem = elem->next;
	}
	return (elem);
}

int	close_pipeline(t_sect *elem)
{
	if (elem->fd->in != STDIN_FILENO)
		close(elem->fd->in);
	if (elem->fd->in != STDOUT_FILENO)
		close(elem->fd->out);
	return (EXIT_SUCCESS);
}

int	open_pipeline(t_sect *elem)
{
	int		fd[2];
	t_sect	*cmd;

	if (elem->type != SECT_TYPE_CMD)
		return (EXIT_FAILURE);
	if (!elem->prev)
		elem->fd->in = STDIN_FILENO;
	if (elem->cmd_type == SECT_CMD_TYPE_END)
		elem->fd->out = STDOUT_FILENO;
	if (elem->cmd_type == SECT_CMD_TYPE_PIPE)
	{
		pipe(fd);
		cmd = get_next_cmd(elem);
		if (!cmd)
			return (EXIT_FAILURE);
		elem->fd->out = fd[1];
		cmd->fd->in = fd[0];
	}
	return (EXIT_SUCCESS);
}
