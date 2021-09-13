/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:36:49 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 16:13:26 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	throw_error_export(char **content, int code)
{
	char	*error;

	if (code == EXPORT_KEY_CONTENT_ERROR)
		error = "export: not valid in this context: ";
	else if (code == EXPORT_KEY_DIGIT_ERROR)
		error = "export: not an identifier: ";
	if (code == EXPORT_KEY_NULL_ERROR)
	{
		ft_putstr_fd("minishell: =", STDERR_FILENO);
		ft_putstr_fd(content[1], STDERR_FILENO);
		ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
		free(content[1]);
		free(content);
		return (set_exit_status(EXIT_FAILURE));
	}
	else
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putendl_fd(content[0], STDERR_FILENO);
	}
	ft_free_args(content);
	return (set_exit_status(EXIT_FAILURE));
}

static int	env_key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (EXPORT_KEY_NULL_ERROR);
	if (ft_isdigit(key[0]))
		return (EXPORT_KEY_DIGIT_ERROR);
	while (key[i])
	{
		if (!ft_isenvkey(key[i]))
			return (EXPORT_KEY_CONTENT_ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}

static char	**split_env_elem(char *arg)
{
	char	**content;
	int		i;
	int		len;

	content = ft_calloc(3, sizeof(char *));
	content[2] = 0;
	len = ft_strlen(arg);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i >= len - 1)
		content[1] = 0;
	else
	{
		if (i == 0)
			len--;
		content[1] = ft_substr(arg, i + 1, len - i);
	}
	if (i < 1)
		content[0] = 0;
	else
		content[0] = ft_substr(arg, 0, i);
	return (content);
}

static int	export_add_elem(char *arg, t_dict *env)
{
	char	**content;
	int		code;
	char	*value;
	t_dict	*elem;

	if (!ft_strchr(arg, '='))
		return (EXIT_FAILURE);
	content = split_env_elem(arg);
	code = env_key_is_valid(content[0]);
	if (code)
		return (throw_error_export(content, code));
	if (!content[1])
		value = ft_strdup("");
	else
		value = ft_strdup(content[1]);
	elem = dict_get_elem(env, content[0]);
	if (elem)
		dict_change_value(elem, value);
	else
		dict_add_elem(&env, dict_init_elem(ft_strdup(content[0]), value));
	ft_free_args(content);
	return (set_exit_status(EXIT_SUCCESS));
}

int	bi_export(char **args, t_dict *env)
{
	int	code;
	int	size;
	int	i;

	size = get_args_size(args);
	if (size == 1)
		return (bi_env(env, args));
	i = 0;
	code = EXIT_SUCCESS;
	while (i < size)
	{
		if (export_add_elem(args[i], env))
			code = EXIT_FAILURE;
		i++;
	}
	return (code);
}
