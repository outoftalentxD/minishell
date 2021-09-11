/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:38:37 by melaena           #+#    #+#             */
/*   Updated: 2021/09/11 16:23:25 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*parser*/
int		preparse(char **str);
t_sect	*parse(char *line);
int		postparse(t_sect **sect);
void	print_sections(t_sect *sect);

/* validator */
int		input_is_valid(t_sect *elem);
int		quotes_is_valid(char *line);
int		sect_set_quotes_flag(int c, int *flag);

/*utils*/
char	*str_replace(char *str, char *replace, char *to, int start);
int		str_change(char **from, char *to);
int		ft_squeeze(char *str, int i);
int		ft_isenvkey(int c);
char	*process_envvar(char *str, int *i);
int		get_next_char_pos(char *line, int start, int c);

/*quotes*/
int		process_squote(char *str, int *i);
int		process_dquote(char **str, int *i);

/*sections*/
t_sect	*sect_init_elem(char *content);
t_sect	*sect_sub_elem(char *str, int start, int len);
int		sect_add_elem(t_sect **sect, t_sect *elem);
int		sect_del_elem(t_sect **sect, t_sect *elem);
int		sect_free_elem(t_sect *elem);
int		get_section_len(char *str, int start, char *set);
int		sect_set_type_to_all(t_sect *sect);
int		sect_define_type(t_sect *sect);
int		sect_is_specified(t_sect *elem);
int		sect_is_rdrct(t_sect *elem);
int		sect_type_is_pipe(t_sect *elem);
char	**sect_form_args(t_sect *sect);
int		sect_set_type(t_sect *elem, int type);
int		sect_set_cmd_type(t_sect *elem, int type);

#endif