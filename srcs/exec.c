/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/22 00:29:04 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_execve(t_lst_cmd *lst_cmd, t_minishell *data)
{
	if (lst_cmd->args[0][0] == '/')
	{
		if (execve(lst_cmd->args[0], lst_cmd->args, data->new_env) < 0)
			return_error_2(lst_cmd->args[0],
				": No such file or directory", 127);
	}
	if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
		return_error_2(lst_cmd->args[0],
			": command not found", 127);
}

void	exec_2(t_lst_cmd *lst_cmd, t_minishell *data)
{
	struct stat	s;
	int			i;

	stat(lst_cmd->args[0], &s);
	if (S_ISDIR(s.st_mode))
		return_error_2(lst_cmd->args[0], ": is a directory", 126);
	if (access(lst_cmd->args[0], X_OK) == -1
		&& access(lst_cmd->args[0], F_OK) == 0)
		return_error_2(lst_cmd->args[0], ": Permission denied", 126);
	if (!ft_strcmp(lst_cmd->args[0], "./minishell"))
	{
		i = find_in_env(data, "SHLVL");
		data->new_env = replace_exist_line_2(data,
				data->new_env[i], data->new_env);
	}
	if (execve(lst_cmd->args[0], lst_cmd->args, data->new_env) == -1)
		return_error_2(lst_cmd->args[0],
			": No such file or directory", 127);
}

int	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		return (return_error_fork());
	else if (lst_cmd->pid == 0)
	{
		init_dup(lst_cmd);
		lst_cmd->path = find_path(data, lst_cmd->args[0]);
		if (ft_strcmp(lst_cmd->path, "nopath") == 0)
			return_error_2(lst_cmd->args[0],
				": No such file or directory", 127);
		if (is_builtin(lst_cmd) != 0)
		{
			do_builtin(data, lst_cmd);
			exit(0);
		}
		else if (lst_cmd->args[0][0] == '.' && lst_cmd->args[0][1] == '/')
			exec_2(lst_cmd, data);
		else
			do_execve(lst_cmd, data);
	}
	return (0);
}

void	close_fds(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->prev != NULL)
		close(lst_cmd->prev->pipe_fd[0]);
	if (lst_cmd->next != NULL)
		close(lst_cmd->pipe_fd[1]);
	if (lst_cmd->fd_in != -1)
		close(lst_cmd->fd_in);
	if (lst_cmd->fd_out != -1)
		close(lst_cmd->fd_out);
}

int	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	while (lst_cmd)
	{
		if (!ft_strlen(lst_cmd->args[0]) && lst_cmd->next)
			return (return_error_syntax());
		lst_cmd = lst_cmd->next;
	}
	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		open_redir(lst_cmd);
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		if (lst_cmd->lst_herdoc)
		{
			if (!lst_cmd->lst_herdoc->file)
				return (return_error_syntax_2());
			ft_heredoc(lst_cmd, data);
		}
		if (is_builtin(lst_cmd) == 2 && !lst_cmd->prev && !lst_cmd->next)
			do_builtin(data, lst_cmd);
		else
		{
			if (ft_fork(lst_cmd, data) == -1)
			{
				close_fds(lst_cmd);
				return (-1);
			}
		}
		close_fds(lst_cmd);
		lst_cmd = lst_cmd->next;
	}
	return (0);
}
