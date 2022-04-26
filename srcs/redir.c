/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/26 14:41:26 by lnemor           ###   ########lyon.fr   */
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

int	open_redir2(t_lst_cmd *lst_cmd)
{
	while (lst_cmd->lst_out->next)
	{
		if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
		{
			if (open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644) < 0)
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
		}
		else
		{
			if (open(lst_cmd->lst_out->file, O_APPEND | O_RDWR
					| O_CREAT, 0644) < 0)
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
		}
		lst_cmd->lst_out = lst_cmd->lst_out->next;
	}
	return (0);
}

int	open_redir3(t_lst_cmd	*lst_cmd)
{
	if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
	{
		//dprintf(2, "file2 %s \n", ft_lstlast_tab(lst_cmd->lst_out)->file);
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (lst_cmd->fd_out < 0)
			return (return_error_redir(lst_cmd->lst_out->file, \
				": Permission denied\n"));
	}
	else
	{
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_APPEND | O_RDWR | O_CREAT, 0644);
		//dprintf(2, "debug %s \n", ft_lstlast_tab(lst_cmd->lst_out)->file);
		if (lst_cmd->fd_out < 0)
			return (return_error_redir(lst_cmd->lst_out->file, \
				": Permission denied\n"));
	}
	return (0);
}

int	open_redir(t_lst_cmd *lst_cmd)
{
	//dprintf(2, "args %s\n", lst_cmd->args[0]); //to delete
	if (lst_cmd->lst_out != NULL)
	{
		if (lst_cmd->lst_out->file)
		{
			if (open_redir2(lst_cmd) == -1)
				return (-1);
			if (open_redir3(lst_cmd) == -1)
				return (-1);
		}
	}
	if (lst_cmd->lst_in != NULL)
	{
		if (lst_cmd->lst_in->file)
		{
			lst_cmd->fd_in = open(ft_lstlast_tab(lst_cmd->lst_in)->file,
					O_RDONLY);
			if (access(lst_cmd->lst_in->file, X_OK) == -1
				&& access(lst_cmd->lst_in->file, F_OK) == 0)
				return (return_error_redir(lst_cmd->lst_in->file, \
					": Permission denied"));
			if (lst_cmd->fd_in < 0)
				return (return_error_redir(lst_cmd->lst_in->file, \
					": No such file or directory\n"));
		}
	}
	if (lst_cmd->next != NULL)
		pipe(lst_cmd->pipe_fd);
	return (0);
}
