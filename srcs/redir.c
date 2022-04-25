/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/25 14:51:27 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->lst_in)
	{
		if (!lst_cmd->lst_in->file)
			return (-1);
	}
	if (lst_cmd->lst_out)
	{
		if (!lst_cmd->lst_out->file)
			return (-1);
	}
	return (0);
}

int	do_heredoc(t_lst_cmd *lst_cmd, t_minishell *data)
{
	if (lst_cmd->lst_herdoc)
	{
		if (!lst_cmd->lst_herdoc->file)
			return (return_error_syntax_2());
		else if (ft_heredoc(lst_cmd, data) == -1)
			return (-1);
	}
	return (0);
}

void	open_redir2(t_lst_cmd *lst_cmd)
{
	while (lst_cmd->lst_out->next)
	{
		if (lst_cmd->lst_out->append == 0)
		{
			if (open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644) < 0)
				return_error(lst_cmd->lst_out->file, ": Permission denied", 1);
		}
		else
		{
			if (open(lst_cmd->lst_out->file, O_APPEND | O_RDWR
					| O_CREAT, 0644) < 0)
				return_error(lst_cmd->lst_out->file, ": Permission denied", 1);
		}
		lst_cmd->lst_out = lst_cmd->lst_out->next;
	}
}

void	open_redir3(t_lst_cmd	*lst_cmd)
{
	if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
	{
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (lst_cmd->fd_out < 0)
			return_error(lst_cmd->lst_out->file,
				": Permission denied", 1);
	}
	else
	{
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_APPEND | O_RDWR | O_CREAT, 0644);
		if (lst_cmd->fd_out < 0)
			return_error(lst_cmd->lst_out->file,
				": Permission denied", 1);
	}
}

void	open_redir(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->next != NULL)
		pipe(lst_cmd->pipe_fd);
	if (lst_cmd->lst_in != NULL)
	{
		if (lst_cmd->lst_in->file)
		{
			lst_cmd->fd_in = open(ft_lstlast_tab(lst_cmd->lst_in)->file,
					O_RDONLY);
			if (lst_cmd->fd_in < 0)
				return_error(lst_cmd->lst_in->file,
					": Permission denied or No such file or directory", 1);
		}
	}
	if (lst_cmd->lst_out != NULL)
	{
		if (lst_cmd->lst_out->file)
		{
			open_redir2(lst_cmd);
			open_redir3(lst_cmd);
		}
	}
}
