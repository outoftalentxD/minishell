/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:19:01 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 15:33:17 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_in_heredoc(char *dlm)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);
	if (fd < 1)
		return (EXIT_FAILURE);
	line = readline("> ");
	if (line)
	{
		while (line && ft_strcmp(line, dlm))
		{
			ft_putendl_fd(line, fd);
			line = readline("> ");
		}
	}
	close(fd);
	if (!line)
	{
		ft_putendl_fd("minshell: warning: here-document delimited by EOF",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	dup_in_rdrct_heredoc(t_sect *elem)
{
	char	*dlm;
	int		fd;
	t_sect	*cmd;

	dlm = ft_strdup(elem->next->content);
	sig_sigint_off();
	elem->pid = fork();
	if (elem->pid == 0)
	{
		signal(SIGINT, sig_heredoc_handler);
		write_in_heredoc(dlm);
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
