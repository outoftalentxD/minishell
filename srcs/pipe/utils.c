/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 20:39:45 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 15:33:10 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_count(t_sect *elem)
{
	int	size;

	size = 0;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			size += 1;
		elem = elem->next;
	}
	return (size);
}

t_sect	*get_next_cmd(t_sect *elem)
{
	elem = elem->next;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

t_sect	*get_prev_cmd(t_sect *elem)
{
	elem = elem->prev;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
			return (elem);
		elem = elem->prev;
	}
	return (NULL);
}

int	close_pipeline(t_sect *elem)
{
	while (elem->prev)
		elem = elem->prev;
	while (elem)
	{
		if (elem->fd->in != STDIN_FILENO)
			close(elem->fd->in);
		if (elem->fd->out != STDOUT_FILENO)
			close(elem->fd->out);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

int	open_pipeline(t_sect *elem)
{
	int		fd[2];
	t_sect	*cmd_prev;
	t_sect	*cmd_next;

	if (elem->type != SECT_TYPE_PIPE)
		return (EXIT_FAILURE);
	cmd_next = get_next_cmd(elem);
	cmd_prev = get_prev_cmd(elem);
	pipe(fd);
	if (cmd_prev)
		cmd_prev->fd->out = fd[1];
	else
		close(fd[1]);
	if (cmd_next)
		cmd_next->fd->in = fd[0];
	else
		close(fd[0]);
	return (EXIT_SUCCESS);
}
