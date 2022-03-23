/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:52:00 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/22 17:31:34 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}

void	do_last_cmd(t_lst_cmd	*lst_cmd)
{
	int	in;

	if (lst_cmd->prev->fd_in != -1)
		in = lst_cmd->prev->fd_in;
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

void	open_redir(t_lst_cmd *lst_cmd)
{
	t_lst_redir	*last_out;
	t_lst_redir	*last_in;

	if (lst_cmd->lst_in->file != NULL)
	{
		last_in = ft_lstlast_tab(lst_cmd->lst_in);
		lst_cmd->fd_in = open(last_in->file, O_RDONLY);
	}
	if (lst_cmd->lst_out->file != NULL)
	{
		while (lst_cmd->lst_out->next)
		{
			if (lst_cmd->lst_out->append == 0)
				open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644);
			else
				open(lst_cmd->lst_out->file, O_APPEND | O_RDWR
					| O_CREAT, 0644);
			lst_cmd->lst_out = lst_cmd->lst_out->next;
		}
		last_out = ft_lstlast_tab(lst_cmd->lst_out);
		if (last_out->append == 0)
			lst_cmd->fd_out = open(last_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644);
		else
			lst_cmd->fd_out = open(last_out->file, O_APPEND | O_RDWR
					| O_CREAT, 0644);
	}
}
