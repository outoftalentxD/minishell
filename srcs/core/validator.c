/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:39:41 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 22:08:56 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_input_error(char *token, int code)
{
	char	*error;

	if (code == INPUT_PARSE_NEAR_TOKEN_ERROR)
		error = "minishell: syntax error near unexpected token '";
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

int sect_is_rdrct(t_sect *elem)
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

int	input_is_valid(t_sect *elem)
{
	if (!elem)
		return (EXIT_FAILURE);
	while (elem)
	{
		if (sect_is_rdrct(elem))
		{
			if (!elem->next)
				return (throw_input_error("newline", INPUT_PARSE_NEAR_TOKEN_ERROR));
			if (sect_is_specified(elem->next))
				return (throw_input_error(elem->next->content, INPUT_PARSE_NEAR_TOKEN_ERROR));		
		}
		else if (sect_type_is_pipe(elem))
		{
			if (!elem->prev || !elem->next)
				return (throw_input_error("|", INPUT_PARSE_NEAR_TOKEN_ERROR));		
		}
		elem = elem->next;
	}
}