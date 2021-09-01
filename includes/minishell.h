/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:16 by melaena           #+#    #+#             */
/*   Updated: 2021/09/01 17:25:42 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "struct.h"
# include "parser.h"
# include "core.h"

# define EXPORT_KEY_CONTENT_ERROR 4001
# define EXPORT_KEY_NULL_ERROR 4002
# define EXPORT_KEY_DIGIT_ERROR 4003

# define UNSET_FEW_ARGS_ERROR 5001
# define UNSET_KEY_CONTENT_ERROR 5002

# define CD_TOO_MANY_ARGS_ERROR 2001
# define CD_WORNG_PATH_ERROR 2002

extern t_mshell	*g_mshell;

#endif
