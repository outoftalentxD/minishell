/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:37:43 by melaena           #+#    #+#             */
/*   Updated: 2021/09/13 15:39:45 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT && g_mshell->signal->sigint)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_mshell->exit_status = 1;
		signal(SIGINT, sig_handler);
	}
}

void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDERR_FILENO);
		unlink(".heredoc");
		free_mshell();
		exit(0);
	}
}

int	set_signal_handlers(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	sig_sigint_off(void)
{
	g_mshell->signal->sigint = 0;
	return (EXIT_SUCCESS);
}

int	sig_sigint_on(void)
{
	g_mshell->signal->sigint = 1;
	return (EXIT_SUCCESS);
}
