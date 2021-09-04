/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbulwer <kbulwer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:16 by melaena           #+#    #+#             */
/*   Updated: 2021/09/04 17:06:58 by kbulwer          ###   ########.fr       */
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
# include <sys/types.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "struct.h"
# include "parser.h"
# include "core.h"

# define SECT_TYPE_PIPE 100001
# define SECT_TYPE_OUT 100002
# define SECT_TYPE_OUT_AP 100003
# define SECT_TYPE_IN 100004
# define SECT_TYPE_IN_DLM 100005
# define SECT_TYPE_ARG 100006
# define SECT_TYPE_CMD 100007

# define EXPORT_KEY_CONTENT_ERROR 4001
# define EXPORT_KEY_NULL_ERROR 4002
# define EXPORT_KEY_DIGIT_ERROR 4003

# define UNSET_FEW_ARGS_ERROR 5001
# define UNSET_KEY_CONTENT_ERROR 5002

# define CD_TOO_MANY_ARGS_ERROR 2001
# define CD_WORNG_PATH_ERROR 2002

# define BIN_COMMAND_NOT_FOUND 8001
# define BIN_NO_FILE_OR_DIR_ERROR 8002
# define BIN_PERMISSION_DENIED_ERROR 8003
# define BIN_IS_DIR_ERROR 8004
# define BIN_ERROR_CODE 8000

# define EXIT_NOT_NUM_ARG_ERROR 9001
# define EXIT_TOO_MANY_ARGS_ERROR 9002

extern t_mshell	*g_mshell;

#endif
