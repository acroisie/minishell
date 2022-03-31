/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/31 15:53:34 by lnemor           ###   ########lyon.fr   */
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

void	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		exit(1);
	else if (lst_cmd->pid == 0)
	{
		init_dup(lst_cmd);
		if (is_builtin(lst_cmd) != 0)
		{
			do_builtin(data, lst_cmd);
			exit(0);
		}
		else if (lst_cmd->args[0][0] == '.' && lst_cmd->args[0][1] == '/')
		{
			execve(lst_cmd->args[0], lst_cmd->args, data->new_env);
		}
		else if (find_path(data, lst_cmd->args[0]) == 0
			&& (lst_cmd->args[0][0] != '/' || (lst_cmd->args[0][0]
			== '/' && lst_cmd->args[0][1] == '/')))
		{
			return_error(lst_cmd->args[0], ": command not found", 127);
			exit (127);
		}
		else
			do_execve(lst_cmd, data);
	}
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
			ft_heredoc(lst_cmd, data);
			lst_cmd->lst_herdoc = lst_cmd->lst_herdoc->next;
		}
		if (is_builtin(lst_cmd) == 2 && !lst_cmd->prev && !lst_cmd->next)
			do_builtin(data, lst_cmd);
		else
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
