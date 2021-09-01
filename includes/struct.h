/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:13 by melaena           #+#    #+#             */
/*   Updated: 2021/09/01 17:21:39 by melaena          ###   ########.fr       */
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
	struct s_dict	*env;
	char			*oldpwd;
}	t_mshell;

#endif
