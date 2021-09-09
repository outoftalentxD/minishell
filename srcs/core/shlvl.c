/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 00:30:18 by melaena           #+#    #+#             */
/*   Updated: 2021/09/10 01:24:53 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inc_shlvl(char **envp)
{
	int		lvl;
	char	*line;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "SHLVL", 5))
			break ;
		envp++;
	}
	if (!*envp)
		return (EXIT_FAILURE);
	line = *envp;
	lvl = ft_atoi(line + 6) + 1;
	*envp = ft_strjoin("SHLVL=", ft_itoa(lvl));
	return (EXIT_SUCCESS);
}
