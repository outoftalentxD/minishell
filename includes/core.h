/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:33:21 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 14:34:33 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"


/* dictionaries utils */
int			dict_add_elem(t_dict **dict, t_dict *elem);
t_dict		*dict_init_elem(char *key, char *value);
char		*dict_get_value(t_dict *dict, char *key);
t_dict		*dict_get_elem(t_dict *dict, char *key);

/* enviroment utils */
t_dict		*init_env(char **env);
t_mshell	*init_mshell(char **env);

/* core funcs */
int	exec_command(char **argv);

/* builtins */
int			bi_echo(char **args);
int			bi_pwd(void);
int			bi_env(t_dict *env);
int			bi_export(char **args, t_dict *env);
int			bi_cd(char **args, t_dict *env);

/* utils */
int			get_args_size(char **args);
int			ft_free_args(char **args);

#endif