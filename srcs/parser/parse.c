/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:28:04 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 18:18:26 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparse(char **strs)
{
	int		i;
	char	*str;
	char	*temp;

	str = *strs;
	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (process_squote(str, &i))
				return (-1);
		}
		// else if (str[i] == '\\')
		// 	ft_squeeze(str, i);
		else if (str[i] == '"')
		{
			if (process_dquote(&str, &i))
				return (-1);
		}
		else if (str[i] == '$')
			str_change(&str, process_envvar(str, &i));
		*strs = str;
	}
	return (0);
}

static void	print_sections(t_sect *sect)
{
	while(sect)
	{
		printf("%s\n", sect->content);
		sect = sect->next;
	}
}

int	sect_merge(t_sect **sect)
{
	t_sect	*elem;

	elem = *sect;
	while (elem->next)
	{
		if (!ft_strcmp(elem->content, ">"))
		{
			if (!ft_strcmp(elem->next->content, ">"))
			{
				sect_del_elem(sect, elem->next);
				free(elem->content);
				elem->content = ft_strdup(">>");
			}
		}
		else if (!ft_strcmp(elem->content, "<"))
		{
			if (!ft_strcmp(elem->next->content, "<"))
			{
				sect_del_elem(sect, elem->next);
				free(elem->content);
				elem->content = ft_strdup("<<");
			}
		}
		elem = elem->next;
	}
	return (0);
}

t_sect  *parse(char *line)
{
	t_sect	*sect;
	char	*args;
	int		i;
	int		len;
	int		sect_len;
	
	i = 0;
	sect = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == ' ')
			i++;
		sect_len = get_section_len(line, i, " <>|");
		sect_add_elem(&sect, sect_sub_elem(line, i, sect_len));
		i += sect_len - 1;
		i++;
	}
	sect_merge(&sect);
	return (sect);
}
