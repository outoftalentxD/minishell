/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:01 by kbulwer           #+#    #+#             */
/*   Updated: 2021/09/09 17:26:00 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_sect *elem)
{
	char	**args;
	int		code;

	if (elem->cmd_type != SECT_CMD_TYPE_END || elem->fd->out != STDOUT_FILENO)
		dup2(elem->fd->out, STDOUT_FILENO);
	if (elem->prev || elem->fd->in != STDIN_FILENO)
		dup2(elem->fd->in, STDIN_FILENO);
	close_pipeline(elem);
	args = sect_form_args(elem);
	code = exec_command(args);
	exit(code);
}

void	process_builtin(t_sect *elem)
{
	char	**args;
	int		code;
	int		fd;
	int		std_fd[2];

	std_fd[0] = dup(STDIN_FILENO);
	std_fd[1] = dup(STDOUT_FILENO);
	if (elem->cmd_type != SECT_CMD_TYPE_END || elem->fd->out != STDOUT_FILENO)
		dup2(elem->fd->out, STDOUT_FILENO);
	if (elem->prev || elem->fd->in != STDIN_FILENO)
		dup2(elem->fd->in, STDIN_FILENO);
	args = sect_form_args(elem);
	code = exec_command(args);
	set_exit_status(code);
	dup2(std_fd[0], STDIN_FILENO);
	dup2(std_fd[1], STDOUT_FILENO);
}

int		get_cmd_count(t_sect *elem)
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

void	process_command(t_sect *elem)
{
	int		status;
	t_sect	*temp;

	status = 0;
	temp = elem;
	while (elem)
		{
			if (elem->type == SECT_TYPE_CMD)
			{
				elem->pid = fork();
				if (elem->pid == 0)
					child_process(elem);
			}
			elem = elem->next;
		}
		elem = temp;
		close_pipeline(elem);
		while (elem)
		{
			if (elem->type == SECT_TYPE_CMD && (!is_builtin(elem->content)))
			{
				waitpid(elem->pid, &status, 0);
				set_exit_status(WEXITSTATUS(status));
			}
			elem = elem->next;
		}
}

void	pipex(t_sect *elem)
{
	if (get_cmd_count(elem) == 1 && is_builtin(elem->content))
		process_builtin(elem);
	else
		process_command(elem);
	close_pipeline(elem);
}
