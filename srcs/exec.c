/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/28 16:00:26 by lnemor           ###   ########lyon.fr   */
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
		pipe(data->pipe_fd);
		lst_cmd->pid = fork();
		if (lst_cmd->pid == -1)
			return ;
		else if (lst_cmd->pid == 0)
		{
			if (lst_cmd->id == 1)
			{
				dup2(data->pipe_fd[1], STDOUT_FILENO);
				close(data->pipe_fd[0]);
			}
			if (!(lst_cmd->id == 1) && !(lst_cmd->next == NULL))
			{
				dup2(data->pipe_fd[1], //test);
				close(data->pipe_fd[0]);
			}
			if (lst_cmd->next == NULL)
			{
				dup2(data->pipe_fd[0], STDIN_FILENO);
				close(data->pipe_fd[1]);
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
