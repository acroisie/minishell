/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/21 17:02:30 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_execve(t_lst_cmd *lst_cmd, t_minishell *data)
{
	if (lst_cmd->args[0][0] == '/')
	{
		if (execve(lst_cmd->args[0], lst_cmd->args, data->new_env) < 0)
			exit(1);
	}
	else
		lst_cmd->path = find_path(data, lst_cmd->args[0]);
	if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
		exit(1);
}

void	exec_2(t_lst_cmd *lst_cmd, t_minishell *data)
{
	struct stat	s;

	stat(lst_cmd->args[0], &s);
	if (S_ISDIR(s.st_mode))
		return_error_2(lst_cmd->args[0], ": is a directory", 126);
	if (access(lst_cmd->args[0], X_OK) == -1
		&& access(lst_cmd->args[0], F_OK) == 0)
		return_error_2(lst_cmd->args[0], ": Permission denied", 126);
	if (execve(lst_cmd->args[0], lst_cmd->args, data->new_env) == -1)
		return_error_2(lst_cmd->args[0],
			": No such file or directory", 127);
}

void	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		exit(1);
	else if (lst_cmd->pid == 0)
	{
		data->error = 00700;
		init_dup(lst_cmd);
		if (is_builtin(lst_cmd) != 0)
		{
			do_builtin(data, lst_cmd);
			exit(0);
		}
		else if (lst_cmd->args[0][0] == '.' && lst_cmd->args[0][1] == '/')
			exec_2(lst_cmd, data);
		else if (find_path(data, lst_cmd->args[0]) == 0
			&& (lst_cmd->args[0][0] != '/' || (lst_cmd->args[0][0]
			== '/' && lst_cmd->args[0][1] == '/')))
		{
			dprintf(2, "path %s\n", lst_cmd->path); 
			return_error(lst_cmd->args[0], ": command not found", 127);
			exit (127);
		}
		else
			do_execve(lst_cmd, data);
	}
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

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		open_redir(lst_cmd);
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		while (lst_cmd->lst_herdoc != NULL)
		{
			if (!lst_cmd->lst_herdoc->file)
				return (return_error("", "error syntax unexpected symbol", 2));
			ft_heredoc(lst_cmd, data);
			lst_cmd->lst_herdoc = lst_cmd->lst_herdoc->next;
		}
		if (is_builtin(lst_cmd) == 2 && !lst_cmd->prev && !lst_cmd->next)
			do_builtin(data, lst_cmd);
		else
			ft_fork(lst_cmd, data);
		close_fds(lst_cmd);
		lst_cmd = lst_cmd->next;
	}
}
