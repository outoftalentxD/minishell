/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:28:04 by melaena           #+#    #+#             */
/*   Updated: 2021/09/12 23:55:20 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparse(char **strs)
{
	int		i;
	char	*str;

	str = *strs;
	i = -1;
	if (!str)
		return (EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (process_squote(str, &i))
				return (EXIT_FAILURE);
		}
		else if (str[i] == '"')
		{
			if (process_dquote(&str, &i))
				return (EXIT_FAILURE);
		}
		else if (str[i] == '$')
			str_change(&str, process_envvar(str, &i));
		*strs = str;
	}
	return (EXIT_SUCCESS);
}

int	process_sections(t_sect *sect)
{
	while (sect)
	{
		if (sect->type == SECT_TYPE_ARG && sect->prev
			&& sect->prev->type == SECT_TYPE_IN_DLM)
		{
			if (preparse_all_quotes(&sect->content))
				return (EXIT_FAILURE);
			sect = sect->next;
			continue ;
		}
		if (preparse(&sect->content))
			return (EXIT_FAILURE);
		sect = sect->next;
	}
	return (EXIT_SUCCESS);
}

int	postparse(t_sect **sect)
{
	t_sect	*elem;

	elem = *sect;
	while (elem)
	{
		if (!elem->content[0] && !elem->quote)
		{
			free(elem->content);
			elem->content = NULL;
			if (elem->type == SECT_TYPE_CMD)
			{
				sect_set_type(elem, SECT_TYPE_NULL);
				if (elem->next && elem->next->type == SECT_TYPE_ARG)
					sect_set_type(elem->next, SECT_TYPE_CMD);
			}
			else
				sect_set_type(elem, SECT_TYPE_NULL);
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

t_sect	*parse(char *line)
{
	t_sect	*sect;
	int		i;
	int		sect_len;

	i = 0;
	sect = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		sect_len = get_section_len(line, i, " <>|");
		sect_add_elem(&sect, sect_sub_elem(line, i, sect_len));
		i += sect_len - 1;
		i++;
		while (line[i] == ' ')
			i++;
	}
	if (sect)
	{
		sect_set_type_to_all(sect);
		process_sections(sect);
	}
	return (sect);
}

t_sect	*parser(void)
{
	char	*line;
	t_sect	*elem;

	line = readline("minishell$ ");
	if (!line)
		process_eof(line);
	if (quotes_is_valid(line))
	{
		free(line);
		return (0);
	}
	elem = parse(line);
	ft_add_history(elem, line);
	free(line);
	postparse(&elem);
	g_mshell->sect = elem;
	return (elem);
}
