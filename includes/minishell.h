/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:56:16 by melaena           #+#    #+#             */
/*   Updated: 2021/09/08 16:29:28 by melaena          ###   ########.fr       */
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

# define SECT_TYPE_PIPE 10001
# define SECT_TYPE_OUT 10002
# define SECT_TYPE_OUT_AP 10003
# define SECT_TYPE_IN 10004
# define SECT_TYPE_IN_DLM 10005
# define SECT_TYPE_ARG 10006
# define SECT_TYPE_CMD 10007

#define SECT_CMD_TYPE_END 10011
#define SECT_CMD_TYPE_PIPE 10012
#define SECT_CMD_TYPE_RDRCT 10013


# define PWD_TOO_MANY_ARGS_ERROR 3001

# define EXPORT_KEY_CONTENT_ERROR 4001
# define EXPORT_KEY_NULL_ERROR 4002
# define EXPORT_KEY_DIGIT_ERROR 4003

# define UNSET_FEW_ARGS_ERROR 5001
# define UNSET_KEY_CONTENT_ERROR 5002

# define ENV_TOO_MANY_ARGS_ERROR 6001

# define CD_TOO_MANY_ARGS_ERROR 2001
# define CD_WORNG_PATH_ERROR 2002

# define BIN_COMMAND_NOT_FOUND 8001
# define BIN_PERMISSION_DENIED_ERROR 8003
# define BIN_IS_DIR_ERROR 8004
# define BIN_ERROR_CODE 8000
# define BIN_NO_FILE_OR_DIR_ERROR 127

# define EXIT_NOT_NUM_ARG_ERROR 9001
# define EXIT_TOO_MANY_ARGS_ERROR 9002

extern t_mshell	*g_mshell;

#endif
