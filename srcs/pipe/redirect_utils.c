/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:19:01 by melaena           #+#    #+#             */
/*   Updated: 2021/09/09 20:26:09 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_in_heredoc(char *dlm)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 1)
		return (EXIT_FAILURE);
	line = readline("> ");
	if (!line)
		return (EXIT_FAILURE);
	while (line && ft_strcmp(line, dlm))
	{
		ft_putendl_fd(line, fd);
		line = readline("> ");
	}
	close(fd);
	if (!line)
	{
		ft_putendl_fd("minshell: warning: here-document delimited by EOF",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
