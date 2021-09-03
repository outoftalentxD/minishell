/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:13 by melaena           #+#    #+#             */
/*   Updated: 2021/09/03 19:50:51 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

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
	char				*oldpwd;
	char				**envp;
}	t_mshell;

typedef struct s_section
{
	struct s_section	*next;
	struct s_section	*prev;
	char				*content;
	int					type;
}	t_sect;

#endif
