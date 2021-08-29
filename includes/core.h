/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:33:21 by melaena           #+#    #+#             */
/*   Updated: 2021/08/29 12:24:00 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"

int			dict_add_elem(t_dict **dict, t_dict *elem);
t_dict		*dict_init_elem(char *key, char *value);
char		*dict_get_value(t_dict *dict, char *key);
t_dict		*dict_get_elem(t_dict *dict, char *key);

t_dict		*init_env(char **env);
t_mshell	*init_mshell(char **env);

#endif