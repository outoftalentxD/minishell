/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:38:58 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 22:41:26 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_out_rdrct(t_sect *elem, int opt)
{
	int		fd;
	t_sect	*cmd;

	if (opt == O_TRUNC)
		fd = open(elem->next->content, O_CREAT | O_WRONLY | O_TRUNC);
	else if (opt == O_APPEND)
		fd = open(elem->next->content, O_CREAT | O_WRONLY | O_APPEND);
	if (fd < 1)
		return (EXIT_FAILURE);
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

static int	dup_in_rdrct_heredoc(t_sect *elem)
{
	char	*dlm;
	char	*line;
	int		fd;
	t_sect	*cmd;

	dlm = ft_strdup(elem->next->content);
	sig_sigint_off();
	elem->pid = fork();
	if (elem->pid == 0)
	{
		signal(SIGINT, sig_heredoc_handler);
		write_in_heredoc(dlm);
		free_mshell();
		exit(0);
	}
	waitpid(elem->pid, 0, 0);
	sig_sigint_on();
	free(dlm);
	cmd = get_prev_cmd(elem);
	if (!cmd)
		return (EXIT_FAILURE);
	fd = open(".heredoc", O_RDONLY | O_CREAT);
	if (cmd->fd->in != STDIN_FILENO)
		close(cmd->fd->in);
	cmd->fd->in = fd;
	return (EXIT_SUCCESS);
}

static int	dup_in_rdrct(t_sect *elem, int opt)
{
	int		fd;
	t_sect	*cmd;

	if (opt == SECT_TYPE_IN)
	{
		fd = open(elem->next->content, O_RDONLY);
		if (fd < 1)
			return (EXIT_FAILURE);
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

int	process_out_rdrct(t_sect *elem)
{
	while (elem)
	{
		if (!elem->next)
			return (EXIT_FAILURE);
		if (elem->type == SECT_TYPE_OUT)
			dup_out_rdrct(elem, O_TRUNC);
		else if (elem->type == SECT_TYPE_OUT_AP)
			dup_out_rdrct(elem, O_APPEND);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

int	process_in_rdrct(t_sect *elem)
{
	while (elem)
	{
		if (!elem->next)
			return (EXIT_FAILURE);
		if (elem->type == SECT_TYPE_IN)
			dup_in_rdrct(elem, SECT_TYPE_IN);
		else if (elem->type == SECT_TYPE_IN_DLM)
			dup_in_rdrct(elem, SECT_TYPE_IN_DLM);
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}