/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:26:48 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:50:58 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_redirect(t_sect *elem)
{
	if (elem->type == SECT_TYPE_IN)
		return (1);
	else if (elem->type == SECT_TYPE_IN_DLM)
		return (1);
	else if (elem->type == SECT_TYPE_OUT)
		return (1);
	else if (elem->type == SECT_TYPE_OUT_AP)
		return (1);
	else
		return (0);
}

int	ft_add_history(t_sect *elem, char *line)
{
	if (!elem)
		return (EXIT_FAILURE);
	while (elem)
	{
		if (elem->type == SECT_TYPE_IN_DLM)
			return (EXIT_FAILURE);
		elem = elem->next;
	}
	add_history(line);
	return (EXIT_SUCCESS);
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

	head = elem;
	while (elem)
	{
		if (elem->type == SECT_TYPE_PIPE)
			open_pipeline(elem);
		elem = elem->next;
	}
	if (process_rdrct(head))
		return ;
	pipex(head);
}
