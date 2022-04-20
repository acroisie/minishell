/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:52:00 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/20 13:09:55 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_in_env(t_minishell *data, char *var_env)
{
	int	j;

	j = -1;
	while (data->new_env[++j])
		if (!ft_strncmp(data->new_env[j], var_env, ft_strlen(var_env)))
			break ;
	return (j);
}

void	do_first_cmd(t_lst_cmd	*lst_cmd)
{
	int	out;

	out = lst_cmd->pipe_fd[1];
	if (lst_cmd->fd_in != -1)
	{
		dup2(lst_cmd->fd_in, STDIN_FILENO);
		close(lst_cmd->fd_in);
	}
	if (lst_cmd->fd_out != -1)
		out = lst_cmd->fd_out;
	dup2(out, STDOUT_FILENO);
	close(out);
	close(lst_cmd->pipe_fd[0]);
}

void	do_mid_cmd(t_lst_cmd	*lst_cmd)
{
	int	in;
	int	out;

	in = lst_cmd->prev->pipe_fd[0];
	out = lst_cmd->pipe_fd[1];
	if (lst_cmd->prev->fd_in != -1)
		in = lst_cmd->prev->fd_in;
	if (lst_cmd->fd_out != -1)
		out = lst_cmd->fd_out;
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
	close(lst_cmd->pipe_fd[0]);
}

void	do_last_cmd(t_lst_cmd	*lst_cmd)
{
	int	in;

	if (lst_cmd->fd_in != -1 && lst_cmd)
		in = lst_cmd->fd_in;
	else
		in = lst_cmd->prev->pipe_fd[0];
	if (lst_cmd->fd_out != -1)
	{
		dup2(lst_cmd->fd_out, STDOUT_FILENO);
		close(lst_cmd->fd_out);
	}
	dup2(in, STDIN_FILENO);
	close(in);
}

void	init_dup(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->prev == NULL && lst_cmd->next != NULL)
		do_first_cmd(lst_cmd);
	if (lst_cmd->prev != NULL && lst_cmd->next != NULL)
		do_mid_cmd(lst_cmd);
	if (lst_cmd->prev != NULL && lst_cmd->next == NULL)
		do_last_cmd(lst_cmd);
	if (lst_cmd->prev == NULL && lst_cmd->next == NULL)
	{
		if (lst_cmd->fd_in != -1)
		{
			dup2(lst_cmd->fd_in, STDIN_FILENO);
			close(lst_cmd->fd_in);
		}
		if (lst_cmd->fd_out != -1)
		{
			dup2(lst_cmd->fd_out, STDOUT_FILENO);
			close(lst_cmd->fd_out);
		}
	}
}
