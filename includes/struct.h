/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:13 by melaena           #+#    #+#             */
/*   Updated: 2021/09/09 20:30:37 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
	struct s_dict	*prev;
}	t_dict;	

typedef struct s_mshell
{
	struct s_dict		*env;
	struct s_section	*sect;
	struct s_signal		*signal;
	struct s_fd			*fd;
	char				*oldpwd;
	char				**envp;
	int					exit_status;
}	t_mshell;

typedef struct s_section
{
	struct s_section	*next;
	struct s_section	*prev;
	char				*content;
	struct s_fd			*fd;
	pid_t				pid;
	int					type;
	int					cmd_type;
}	t_sect;

typedef struct s_signal
{
	int	sigint;
}	t_sig;

#endif
