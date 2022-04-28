/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/28 11:39:25 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir(t_lst_cmd *lst_cmd)
{
	while (lst_cmd)
	{
		if (!ft_strlen(lst_cmd->args[0]) && lst_cmd->next
			&& !lst_cmd->lst_herdoc && !lst_cmd->lst_out
			&& !lst_cmd->lst_in)
			return (return_error_syntax());
		if (lst_cmd->lst_in)
			if (!ft_strlen(lst_cmd->lst_in->file))
				return (return_error_syntax_redir());
		if (lst_cmd->lst_out)
			if (!ft_strlen(lst_cmd->lst_out->file))
				return (return_error_syntax_redir());
		if (lst_cmd->lst_herdoc)
			if (!ft_strlen(lst_cmd->lst_herdoc->file))
				return (return_error_syntax_redir());
		lst_cmd = lst_cmd->next;
	}
	return (0);
}

//int	open_prev_fd(t_lst_cmd *lst_cmd, int fd)
//{
//	
//	return (0);
//}

int	open_redir2(t_lst_cmd *lst_cmd, struct stat *s)
{
	int		fd;

	stat(lst_cmd->lst_out->file, s);
	while (lst_cmd->lst_out->next)
	{
		if (ft_strlen(lst_cmd->lst_out->file))
		{
			if (lst_cmd->lst_out->append == 0)
			{
				fd = open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR
						| O_CREAT, 0644);
				if (fd < 0)
				{
					close(fd);
					if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
						return (return_error_redir(lst_cmd->lst_out->file, \
							": No such file or directory\n"));
					return (return_error_redir(lst_cmd->lst_out->file, \
						": Permission denied\n"));
				}
			}
			else
			{
				fd = open(lst_cmd->lst_out->file, O_APPEND | O_RDWR
						| O_CREAT, 0644);
				if (fd < 0)
				{
					close(fd);
					if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
						return (return_error_redir(lst_cmd->lst_out->file, \
							": No such file or directory\n"));
					return (return_error_redir(lst_cmd->lst_out->file, \
						": Permission denied\n"));
				}
			}
			close(fd);
		}
		else
			return (return_error_redir(lst_cmd->lst_out->file, \
						": syntax error near unexpected token `newline'\n"));
		lst_cmd->lst_out = lst_cmd->lst_out->next;
	}
	return (0);
}

int	open_redir3(t_lst_cmd	*lst_cmd, struct stat *s)
{
	stat(lst_cmd->lst_out->file, s);
	if (ft_strlen(ft_lstlast_tab(lst_cmd->lst_out)->file))
	{
		if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
		{
			lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
					O_TRUNC | O_RDWR | O_CREAT, 0644);
			if (lst_cmd->fd_out < 0)
			{
				if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
					return (return_error_redir(lst_cmd->lst_out->file, \
						": No such file or directory\n"));
				return (return_error_redir(lst_cmd->lst_out->file, \
					": Permission denied\n"));
			}
		}
		else
		{
			lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
					O_APPEND | O_RDWR | O_CREAT, 0644);
			if (lst_cmd->fd_out < 0)
			{
				if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
					return (return_error_redir(lst_cmd->lst_out->file, \
						": No such file or directory\n"));
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

	if (lst_cmd->next != NULL)
		pipe(lst_cmd->pipe_fd);
	if (lst_cmd->lst_out != NULL)
	{
		if (ft_strlen(lst_cmd->lst_out->file))
			if (open_redir2(lst_cmd, &s) == -1
				|| open_redir3(lst_cmd, &s) == -1)
				return (-1);
	}
	if (lst_cmd->lst_in != NULL)
	{
		stat(lst_cmd->lst_in->file, &s);
		lst_cmd->fd_in = open(ft_lstlast_tab(lst_cmd->lst_in)->file,
				O_RDONLY);
		if (lst_cmd->fd_in < 0)
		{
			if (!S_ISDIR(s.st_mode) && !S_ISREG(s.st_mode))
				return (return_error_redir(lst_cmd->lst_in->file, \
					": No such file or directory\n"));
			return (return_error_redir(lst_cmd->lst_in->file, \
				": Permission denied\n"));
		}
	}
	return (0);
}
