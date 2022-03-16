/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/16 16:55:45 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_first_cmd(t_lst_cmd	*lst_cmd)
{
	if (lst_cmd->fd_in != 0)
	{
		dup2(lst_cmd->fd_in, STDIN_FILENO);
		close(lst_cmd->fd_in);
	}
	if (lst_cmd->fd_out != 0)
	{
		dup2(lst_cmd->fd_out, STDOUT_FILENO);
		close(lst_cmd->fd_out);
	}
	else
	{
		dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
		close(lst_cmd->pipe_fd[1]);
	}
}

void	do_mid_cmd(t_lst_cmd	*lst_cmd)
{
	if (lst_cmd->prev->fd_in != 0)
	{
		dup2(lst_cmd->prev->fd_in, STDIN_FILENO);
		close(lst_cmd->prev->fd_in);
	}
	if (lst_cmd->fd_out != 0)
	{
		dup2(lst_cmd->fd_out, STDOUT_FILENO);
		close(lst_cmd->fd_out);
	}
	else
	{
		dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
		dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
		close(lst_cmd->prev->pipe_fd[0]);
		close(lst_cmd->pipe_fd[1]);
	}
}

void	do_last_cmd(t_lst_cmd	*lst_cmd)
{
	if (lst_cmd->prev->fd_in != 0)
	{
		dup2(lst_cmd->prev->fd_in, STDIN_FILENO);
		close(lst_cmd->prev->fd_in);
	}
	if (lst_cmd->fd_out != 0)
	{
		dup2(lst_cmd->fd_out, STDOUT_FILENO);
		close(lst_cmd->fd_out);
	}
	else
	{
		dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
		close(lst_cmd->prev->pipe_fd[0]);
	}
}

void	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		exit(1);
	else if (lst_cmd->pid == 0)
	{
		if (lst_cmd->prev == NULL && lst_cmd->next != NULL)
			do_first_cmd(lst_cmd);
		if (lst_cmd->prev != NULL && lst_cmd->next != NULL)
			do_mid_cmd(lst_cmd);
		if (lst_cmd->prev != NULL && lst_cmd->next == NULL)
			do_last_cmd(lst_cmd);
		if (lst_cmd->prev == NULL && lst_cmd->next == NULL)
		{
			if (lst_cmd->fd_in != 0)
			{
				dup2(lst_cmd->fd_in, STDIN_FILENO);
				close(lst_cmd->fd_in);
			}
			if (lst_cmd->fd_out != 0)
			{
				dup2(lst_cmd->fd_out, STDOUT_FILENO);
				close(lst_cmd->fd_out);
			}
		}
		if (find_path(data, lst_cmd->args[0]) == 0
			&& lst_cmd->args[0][0] != '/')
		{
			ft_putstr_fd("command not found\n", 2);
			exit (0);
		}
		if (is_builtin(lst_cmd) == 0)
		{
			if (lst_cmd->args[0][0] == '/')
				execve(lst_cmd->args[0], lst_cmd->args, data->new_env);
			else
				lst_cmd->path = find_path(data, lst_cmd->args[0]);
			if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
				exit(1);
		}
		if (is_builtin(lst_cmd) == 1)
		{
			do_builtin(data, lst_cmd);
			exit (1);
		}
	}
	return ;
}

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	t_lst_redir	*last_out;
	t_lst_redir	*last_in;

	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		if (lst_cmd->lst_in->file != NULL)
		{
			last_in = ft_lstlast_tab(lst_cmd->lst_in);
			lst_cmd->fd_in = open(last_in->file, O_RDONLY);
		}
		if (lst_cmd->lst_out->file != NULL)
		{
			while (lst_cmd->lst_out->next)
			{
				open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644);
				lst_cmd->lst_out = lst_cmd->lst_out->next;
			}
			last_out = ft_lstlast_tab(lst_cmd->lst_out);
			lst_cmd->fd_out = open(last_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644);
		}
		ft_fork(lst_cmd, data);
		if (lst_cmd->prev != NULL)
			close(lst_cmd->prev->pipe_fd[0]);
		if (lst_cmd->next != NULL)
			close(lst_cmd->pipe_fd[1]);
		if (lst_cmd->fd_in != 0)
			close(lst_cmd->fd_in);
		if (lst_cmd->fd_out != 0)
			close(lst_cmd->fd_out);
		lst_cmd = lst_cmd->next;
	}
	lst_cmd = data->start_cmd;
}
