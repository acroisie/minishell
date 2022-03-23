/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/22 17:36:41 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char	*line;

	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		exit(1);
	else if (lst_cmd->pid == 0)
	{
		init_dup(lst_cmd);
		if (find_path(data, lst_cmd->args[0]) == 0
			&& lst_cmd->args[0][0] != '/' && is_builtin(lst_cmd) == 0)
		{
			ft_putstr_fd("command not found\n", 2);
			exit (0);
		}
		else if (is_builtin(lst_cmd) == 0)
		{
			if (lst_cmd->args[0][0] == '/')
				execve(lst_cmd->args[0], lst_cmd->args, data->new_env);
			else
				lst_cmd->path = find_path(data, lst_cmd->args[0]);
			if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
				exit(1);
		}
		else if (is_builtin(lst_cmd) == 1)
			do_builtin(data, lst_cmd);
	}
	return ;
}

int	ft_heredoc(t_lst_cmd *lst_cmd)
{
	char	*line;
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		while (1)
		{
			line = readline(">");
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) != 0)
				ft_putendl_fd(line, fds[1]);
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) == 0)
			{
				free(line);
				exit(0);
			}
			free(line);
		}
	}
	else
	{
		waitpid(pid, 0, 0);
		close(fds[1]);
		if (lst_cmd->lst_herdoc->next == NULL)
			lst_cmd->fd_in = fds[0];
		if (lst_cmd->lst_herdoc->next)
			close(fds[0]);
	}
	return (0);
}

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	lst_cmd = data->start_cmd;
	lst_cmd->lst_herdoc = ft_create_tab("a");
	lst_cmd->lst_herdoc->next = ft_create_tab("b");
	//lst_cmd->next->lst_herdoc = ft_create_tab("a");
	//lst_cmd->next->lst_herdoc->next = ft_create_tab("b");
	while (lst_cmd)
	{
		open_redir(lst_cmd);
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		if (lst_cmd->lst_herdoc)
		{
			while (lst_cmd->lst_herdoc)
			{
				ft_heredoc(lst_cmd);
				lst_cmd->lst_herdoc = lst_cmd->lst_herdoc->next;
			}
		}
		ft_fork(lst_cmd, data);
		if (lst_cmd->prev != NULL)
			close(lst_cmd->prev->pipe_fd[0]);
		if (lst_cmd->next != NULL)
			close(lst_cmd->pipe_fd[1]);
		if (lst_cmd->fd_in != -1)
			close(lst_cmd->fd_in);
		if (lst_cmd->fd_out != -1)
			close(lst_cmd->fd_out);
		lst_cmd = lst_cmd->next;
	}
	lst_cmd = data->start_cmd;
}