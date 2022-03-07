/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/07 18:00:03 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fork(t_lst_cmd *lst_cmd, t_minishell *data)
{
	lst_cmd->pid = fork();
	if (lst_cmd->pid == -1)
		exit(1);
	else if (lst_cmd->pid == 0)
	{
		if (lst_cmd->prev == NULL && lst_cmd->next != NULL)
		{
			dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
			close(lst_cmd->pipe_fd[1]);
		}
		if (lst_cmd->prev != NULL && lst_cmd->next != NULL)
		{
			dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
			dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
			close(lst_cmd->prev->pipe_fd[0]);
			close(lst_cmd->pipe_fd[1]);
		}
		if (lst_cmd->prev != NULL && lst_cmd->next == NULL)
		{
			dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
			close(lst_cmd->prev->pipe_fd[0]);
		}
		if (find_path(data, lst_cmd->args[0]) == 0)
		{
			ft_putstr_fd("command not found\n", 2);
			exit (0);
		}
		lst_cmd->path = find_path(data, lst_cmd->args[0]);
		if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
			exit(1);
	}
	return ;
}

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		ft_fork(lst_cmd, data);
		if (lst_cmd->prev != NULL)
			close(lst_cmd->prev->pipe_fd[0]);
		if (lst_cmd->next != NULL)
			close(lst_cmd->pipe_fd[1]);
		lst_cmd = lst_cmd->next;
	}
	lst_cmd = data->start_cmd;
}
