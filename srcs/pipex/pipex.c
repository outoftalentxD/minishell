/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:02:01 by kbulwer           #+#    #+#             */
/*   Updated: 2021/09/07 18:02:03 by kbulwer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_sect *elem)
{
	char	**args;
	int		code;

	if (elem->cmd_type != SECT_CMD_TYPE_END)
		dup2(elem->fd->out, 1);
	if (elem->prev)
		dup2(elem->fd->in, 0);
	close_pipeline(elem);
	args = sect_form_args(elem);
	code = exec_command(args);
	exit(code);
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
		if (elem->type == SECT_TYPE_CMD)
		{
			waitpid(elem->pid, &status, 0);
		}
		elem = elem->next;
	}
}
