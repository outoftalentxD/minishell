/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:01 by kbulwer           #+#    #+#             */
/*   Updated: 2021/09/08 19:42:17 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_sect *elem)
{
	char	**args;
	int		code;

	if (elem->cmd_type != SECT_CMD_TYPE_END || elem->fd->out != STDOUT_FILENO)
		dup2(elem->fd->out, 1);
	if (elem->prev || elem->fd->in != STDIN_FILENO)
		dup2(elem->fd->in, 0);
	close_pipeline(elem);
	args = sect_form_args(elem);
	code = exec_command(args);
}

void	bi_child_process(t_sect *elem)
{
	char	**args;
	int		code;

	if (elem->cmd_type != SECT_CMD_TYPE_END || elem->fd->out != STDOUT_FILENO)
		dup2(elem->fd->out, 1);
	if (elem->prev || elem->fd->in != STDIN_FILENO)
		dup2(elem->fd->in, 0);
	args = sect_form_args(elem);
	code = exec_command(args);
	set_exit_status(code);
}

void	pipex(t_sect *elem)
{
	int		status;
	t_sect	*temp;

	status = 0;
	temp = elem;
	while (elem)
	{
		if (elem->type == SECT_TYPE_CMD)
		{
			if (is_builtin(elem->content))
			{
				bi_child_process(elem);
			}
			else
			{
				elem->pid = fork();
				if (elem->pid == 0)
					child_process(elem);
			}
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
