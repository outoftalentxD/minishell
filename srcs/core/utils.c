/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:26:48 by melaena           #+#    #+#             */
/*   Updated: 2021/09/09 20:26:47 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_status(int status)
{
	g_mshell->exit_status = status;
	return (status);
}

int	set_signal_handlers(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

char	*bin_form_path(char *name, char *path)
{
	char	*temp;
	char	*ret;

	temp = ft_strjoin(path, "/");
	ret = ft_strjoin(temp, name);
	free(temp);
	return (ret);
}

void	cmd_execution(t_sect *elem)
{
	t_sect	*head;
	pid_t	child;

	head = elem;
	while (elem)
	{
		if (elem->type == SECT_TYPE_PIPE)
			open_pipeline(elem);
		elem = elem->next;
	}
	process_out_rdrct(head);
	process_in_rdrct(head);
	pipex(head);
}
