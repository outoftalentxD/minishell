/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:39:41 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 15:16:42 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_input_error(char *token, int code)
{
	char	*error;

	error = NULL;
	if (code == INPUT_TOKEN_ERROR)
		error = "minishell: syntax error near unexpected token '";
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	set_exit_status(2);
	return (EXIT_FAILURE);
}

int	sect_is_rdrct(t_sect *elem)
{
	if (elem->type == SECT_TYPE_OUT)
		return (1);
	else if (elem->type == SECT_TYPE_OUT_AP)
		return (1);
	else if (elem->type == SECT_TYPE_IN)
		return (1);
	else if (elem->type == SECT_TYPE_OUT)
		return (1);
	else
		return (0);
}

int	sect_set_quotes_flag(int c, int *flag)
{
	if (c == '"' && *flag == 0)
		*flag = '"';
	else if (c == '"' && *flag == '"')
		*flag = 0;
	else if (c == '\'' && *flag == 0)
		*flag = '\'';
	else if (c == '\'' && *flag == '\'')
		*flag = 0;
	return (EXIT_SUCCESS);
}

int	quotes_is_valid(char *line)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (line[i])
	{
		sect_set_quotes_flag(line[i], &flag);
		i++;
	}
	if (!flag)
		return (EXIT_SUCCESS);
	else
	{
		if (flag == '\'')
			ft_putendl_fd("minishell: bad sequence of single quotes",
				STDERR_FILENO);
		else if (flag == '\"')
			ft_putendl_fd("minishell: bad sequence of double quotes",
				STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}

int	input_is_valid(t_sect *elem)
{
	if (!elem)
		return (EXIT_FAILURE);
	while (elem)
	{
		if (sect_is_rdrct(elem))
		{
			if (!elem->next)
				return (throw_input_error("newline", INPUT_TOKEN_ERROR));
			if (sect_is_specified(elem->next))
				return (throw_input_error(elem->next->content,
						INPUT_TOKEN_ERROR));
		}
		else if (sect_type_is_pipe(elem))
		{
			if (!elem->prev || !elem->next)
				return (throw_input_error("|", INPUT_TOKEN_ERROR));
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}
