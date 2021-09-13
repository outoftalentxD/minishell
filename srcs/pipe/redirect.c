/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:38:58 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 15:16:57 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_rdrct(char *token, int code)
{
	if (code == RDRCT_FILE_ERROR)
	{
		if (!token)
			ft_putendl_fd("minishell: no such file or directory:",
				STDERR_FILENO);
		else
		{
			ft_putstr_fd("minishell: no such file or directory: ",
				STDERR_FILENO);
			ft_putendl_fd(token, STDERR_FILENO);
		}
	}
	set_exit_status(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static int	dup_out_rdrct(t_sect *elem, int opt)
{
	int		fd;
	t_sect	*cmd;

	fd = 0;
	if (opt == SECT_TYPE_OUT)
		fd = open(elem->next->content, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (opt == SECT_TYPE_OUT_AP)
		fd = open(elem->next->content, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd < 1)
		return (throw_error_rdrct(elem->next->content, RDRCT_FILE_ERROR));
	cmd = get_prev_cmd(elem);
	if (!cmd)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	if (cmd->fd->out != STDOUT_FILENO)
		close(cmd->fd->out);
	cmd->fd->out = fd;
	return (EXIT_SUCCESS);
}

static int	dup_in_rdrct(t_sect *elem, int opt)
{
	int		fd;
	t_sect	*cmd;

	if (opt == SECT_TYPE_IN)
	{
		fd = open(elem->next->content, O_RDONLY, S_IRWXU);
		if (fd < 1)
			return (throw_error_rdrct(elem->next->content, RDRCT_FILE_ERROR));
		cmd = get_prev_cmd(elem);
		if (!cmd)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		if (cmd->fd->in != STDIN_FILENO)
			close(cmd->fd->in);
		cmd->fd->in = fd;
	}
	else if (opt == SECT_TYPE_IN_DLM)
		dup_in_rdrct_heredoc(elem);
	return (EXIT_SUCCESS);
}

int	process_rdrct(t_sect *elem)
{
	int	code;

	code = 0;
	while (elem)
	{
		if (!elem->next)
			return (EXIT_SUCCESS);
		if (elem->type == SECT_TYPE_IN)
			code = dup_in_rdrct(elem, SECT_TYPE_IN);
		else if (elem->type == SECT_TYPE_IN_DLM)
			code = dup_in_rdrct(elem, SECT_TYPE_IN_DLM);
		else if (elem->type == SECT_TYPE_OUT)
			code = dup_out_rdrct(elem, SECT_TYPE_OUT);
		else if (elem->type == SECT_TYPE_OUT_AP)
			code = dup_out_rdrct(elem, SECT_TYPE_OUT_AP);
		if (code)
			return (EXIT_FAILURE);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}
