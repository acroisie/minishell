/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/08 10:42:57 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	t_lst_cmd	*start;
	int			i;

	start = lst_cmd;
	i = 0;
	while (lst_cmd)
	{
		pipe(lst_cmd->pipe_fd);
		lst_cmd->pid = fork();
		if (lst_cmd->pid == -1)
			exit(1);
		else if (lst_cmd->pid == 0)
		{
			if (lst_cmd->prev == NULL && lst_cmd->next != NULL)
			{
				dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
				close(lst_cmd->pipe_fd[0]);
			}
			else if (lst_cmd->prev != NULL && lst_cmd->next != NULL)
			{
				dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
				dup2(lst_cmd->pipe_fd[1], STDOUT_FILENO);
				close(lst_cmd->pipe_fd[0]);
				close(lst_cmd->prev->pipe_fd[1]);
			}
			else if (lst_cmd->prev != NULL && lst_cmd->next == NULL)
			{
				dup2(lst_cmd->prev->pipe_fd[0], STDIN_FILENO);
				close(lst_cmd->prev->pipe_fd[1]);
				close(lst_cmd->pipe_fd[0]);
				close(lst_cmd->pipe_fd[1]);
			}
			if (find_path(data, lst_cmd->args[0]) == 0)
			{
				ft_putstr_fd("command(1) not found\n", 2);
				exit (0);
			}
			lst_cmd->path = find_path(data, lst_cmd->args[0]);
			execve(lst_cmd->path, lst_cmd->args, data->new_env);
		}
		lst_cmd = lst_cmd->next;
		i++;
	}
	lst_cmd = start;
}
