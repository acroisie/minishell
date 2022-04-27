/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 16:39:02 by lnemor           ###   ########lyon.fr   */
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
	int		fd;

	if (ft_strlen(lst_cmd->lst_out->file))
	{
		if (lst_cmd->lst_out->append == 0)
		{
			fd = open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
					| O_CREAT, 0644);
			if (fd < 0)
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
		}
		else
		{
			fd = open(lst_cmd->lst_out->file, O_APPEND | O_RDWR
					| O_CREAT, 0644);
			if (fd < 0)
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
		}
		close(fd);
	}
	else
		return (return_error_redir(lst_cmd->lst_out->file, \
					": syntax error near unexpected token `newline'\n"));
	lst_cmd->lst_out = lst_cmd->lst_out->next;
	return (0);
}

int	open_redir3(t_lst_cmd	*lst_cmd)
{
	if (ft_strlen(ft_lstlast_tab(lst_cmd->lst_out)->file))
	{
		if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
		{
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
			if (lst_cmd->fd_out < 0)
			{
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
			}
		}
	}
	else
		return (return_error_redir(ft_lstlast_tab(lst_cmd->lst_out)->file, \
					": syntax error near unexpected token `newline'\n"));
	return (0);
}

int	open_redir(t_lst_cmd *lst_cmd)
{
	struct stat	s;

	if (lst_cmd->lst_out != NULL)
	{
		if (ft_strlen(lst_cmd->lst_out->file))
			if (open_redir2(lst_cmd) == -1 || open_redir3(lst_cmd) == -1)
				return (-1);
	}
	if (lst_cmd->lst_in != NULL)
	{
		stat(lst_cmd->lst_in->file, &s);
		if (!S_ISDIR(s.st_mode) && !S_ISREG(s.st_mode))
			return (return_error_redir(lst_cmd->lst_in->file, \
					": No such file or directory\n"));
		lst_cmd->fd_in = open(ft_lstlast_tab(lst_cmd->lst_in)->file,
				O_RDONLY);
		if (lst_cmd->fd_in < 0)
		{
			return (return_error_redir(lst_cmd->lst_in->file, \
				": Permission denied\n"));
		}
	}
	return (0);
}
