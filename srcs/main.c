/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melaena <melaena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:16:39 by melaena           #+#    #+#             */
/*   Updated: 2021/09/08 19:41:00 by melaena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_mshell;

void	print_sections(t_sect *elem)
{
	while (elem)
	{
		printf("content: %s type %d cmdtype %d\n", elem->content, elem->type, elem->cmd_type);
		elem = elem->next;
	}
}

int		process_out_rdrct(t_sect *elem)
{
	t_sect	*cmd;
	int		fd;
	while (elem)
	{
		if (elem->type == SECT_TYPE_OUT)
		{
			if (!elem->next)
				return (EXIT_FAILURE);
			fd = open(elem->next->content, O_CREAT | O_WRONLY | O_TRUNC);
			if (fd < 1)
				return (EXIT_FAILURE);
			cmd = get_prev_cmd(elem);
			if (cmd->fd->out != STDOUT_FILENO)
				close(cmd->fd->out);
			cmd->fd->out = fd;
		}
		else if (elem->type == SECT_TYPE_OUT_AP)
		{
			if (!elem->next)
				return (EXIT_FAILURE);
			fd = open(elem->next->content, O_CREAT | O_WRONLY | O_APPEND);
			if (fd < 1)
				return (EXIT_FAILURE);
			cmd = get_prev_cmd(elem);
			if (cmd->fd->out != STDOUT_FILENO)
				close(cmd->fd->out);
			cmd->fd->out = fd;
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

int	process_in_rdrct(t_sect *elem)
{
	t_sect	*cmd;
	int		fd;

	char	*dlm;
	char	*line;

	while (elem)
	{
		if (elem->type == SECT_TYPE_IN)
		{
			if (!elem->next)
				return (EXIT_FAILURE);
			fd = open(elem->next->content, O_RDONLY);
			if (fd < 1)
				return (EXIT_FAILURE);
			cmd = get_prev_cmd(elem);
			if (cmd->fd->in != STDIN_FILENO)
				close(cmd->fd->in);
			cmd->fd->in = fd;
		}
		else if (elem->type == SECT_TYPE_IN_DLM)
		{
			if (!elem->next)
				return (EXIT_FAILURE);
			dlm = ft_strdup(elem->next->content);
			fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC);
			if (fd < 1)
				return (EXIT_FAILURE);
			line = readline("> ");
			if (!line)
				return (EXIT_FAILURE);
			while (ft_strcmp(line, dlm))
			{
				ft_putendl_fd(line, fd);
				line = readline("> ");
			}
			cmd = get_prev_cmd(elem);
			close(fd);
			fd = open(".heredoc", O_RDONLY);
			if (cmd->fd->in != STDIN_FILENO)
				close(cmd->fd->in);
			cmd->fd->in = fd;
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

void	cmd_execution(t_sect *elem)
{
	t_sect	*head;
	pid_t	child;

	head = elem;
	while (elem)
	{
		if (elem->type == SECT_TYPE_PIPE)
			open_pipeline(elem);
		elem = elem->next;
	}
	process_out_rdrct(head);
	process_in_rdrct(head);
	pipex(head);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_sect	*elem;
	char	**args;

	g_mshell = init_mshell(env);
	while (1)
	{
		set_signal_handlers();
		line = readline("minishell$ ");
		if (!line)
			return (0);
		add_history(line);
		elem = parse(line);
		if (!elem)
			continue ;
		// print_sections(elem);
		// args = sect_form_args(elem);
		// while (*args)
		// 	printf("arg: %s\n", *args++);			
		
		cmd_execution(elem);
		unlink(".heredoc");
	}
	return (EXIT_SUCCESS);
}
