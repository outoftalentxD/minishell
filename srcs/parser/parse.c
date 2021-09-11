/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:28:04 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 15:31:19 by melaena          ###   ########.fr       */
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

static int	preparse_quotes(char *str, int *i)
{
	int	j;
	int	c;

	j = *i;
	c = str[j];
	printf("c = %c\n", c);
	ft_squeeze(str, j);
	while (str[j])
	{
		if (str[j] == c)
		{
			ft_squeeze(str, j);
			*i = j - 1;
			return (EXIT_SUCCESS);
		}
		j++;
	}
	ft_putstr_fd("Bad sequence of single quotes\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	preparse_all_quotes(char **strs)
{
	int		i;
	char	*str;

	str = *strs;
	i = -1;
	if (!str)
		return (EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (preparse_quotes(str, &i))
				return (EXIT_FAILURE);
		}
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
			preparse_all_quotes(&sect->content);
			sect = sect->next;
			continue ;
		}
		preparse(&sect->content);
		sect = sect->next;
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
