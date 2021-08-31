/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:36:49 by melaena           #+#    #+#             */
/*   Updated: 2021/08/31 14:47:50 by melaena          ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(content[1], STDERR_FILENO);
		ft_putendl_fd(" not found", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putendl_fd(content[0], STDERR_FILENO);
	}
	ft_free_args(content);
	return (0);
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
	return (0);
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
		content[1] = ft_substr(arg, i + 1, len - i);
	if (i < 1)
		content[0] = 0;
	else
		content[0] = ft_substr(arg, 0, i);
	return (content);
}

int	bi_export(char **args, t_dict *env)
{
	char	**content;
	int		code;
	int		size;
	char	*value;
	t_dict	*elem;

	size = get_args_size(args);
	if (size == 1)
		return (bi_env(env));
	content = split_env_elem(args[1]);
	code = env_key_is_valid(content[0]);
	if (code)
		return (throw_error_export(content, code));
	if (!content[1])
		value = ft_strdup("");
	else
		value = ft_strdup(content[1]);
	elem = dict_get_elem(env, content[0]);
	if (elem)
		elem->value = value;
	else
		dict_add_elem(&env, dict_init_elem(ft_strdup(content[0]), value));
	ft_free_args(content);
	return (0);
}
