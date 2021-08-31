/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 01:38:37 by melaena           #+#    #+#             */
/*   Updated: 2021/08/30 16:37:54 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*parser*/
int		preparse(char **str);

/*utils*/
char	*str_replace(char *str, char *replace, char *to, int start);
int		str_change(char **from, char *to);
int		ft_squeeze(char *str, int i);
int		ft_isenvkey(int c);
char	*process_envvar(char *str, int *i);

/*quotes*/
int		process_squote(char *str, int *i);
int		process_dquote(char **str, int *i);

#endif