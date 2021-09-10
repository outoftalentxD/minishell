/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:26:48 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 12:24:26 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_eof(void)
{
	printf("exit\n");
	exit(0);
}

int	set_exit_status(int status)
{
	g_mshell->exit_status = status;
	return (status);
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
