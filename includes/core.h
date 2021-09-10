/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 03:33:21 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 12:28:59 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "minishell.h"

/* dictionaries utils */
t_dict		*dict_init_elem(char *key, char *value);
t_dict		*dict_get_elem(t_dict *dict, char *key);
int			dict_add_elem(t_dict **dict, t_dict *elem);
int			dict_free_elem(t_dict *elem);
int			dict_del_by_key(t_dict **dict, char *key);
int			dict_del_elem(t_dict **dict, t_dict *elem);
char		*dict_get_value(t_dict *dict, char *key);
int			dict_change_value(t_dict *elem, char *value);
int			dict_change_value_dup(t_dict *elem, char *value);

/* enviroment utils */
t_dict		*init_env(char **env);
t_mshell	*init_mshell(char **env);
t_sig		*init_signal(void);

/* exec command */
int			exec_command(char **argv);
int			exec_binary(char **args, char **envp);
int			is_builtin(char *arg);

/* builtins */
int			bi_echo(char **args);
int			bi_pwd(char **args);
int			bi_env(t_dict *env, char **args);
int			bi_export(char **args, t_dict *env);
int			bi_cd(char **args, t_dict *env);
int			bi_unset(char **args, t_dict **env);
int			bi_exit(char **args);

/* utils */
int			get_args_size(char **args);
int			ft_free_args(char **args);
int			set_exit_status(int status);
char		*bin_form_path(char *name, char *path);
int			inc_shlvl(char **envp);
int			process_eof(void);

/* signal */
void		sig_handler(int signum);
int			set_signal_handlers(void);
int			sig_sigint_on(void);
int			sig_sigint_off(void);
void		sig_heredoc_handler(int signum);

/* pipex */
void		pipex(t_sect *elem);
void		cmd_execution(t_sect *elem);
int			close_pipeline(t_sect *elem);
int			open_pipeline(t_sect *elem);
t_sect		*get_next_cmd(t_sect *elem);
t_sect		*get_prev_cmd(t_sect *elem);
int			get_cmd_count(t_sect *elem);

/* redirect */
int			process_out_rdrct(t_sect *elem);
int			process_in_rdrct(t_sect *elem);
int			write_in_heredoc(char *dlm);

#endif