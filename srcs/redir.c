/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/28 14:21:29 by lnemor           ###   ########lyon.fr   */
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

int	open_prev_fd(t_lst_cmd *lst_cmd, struct stat *s, int *f)
{
	*f = open(lst_cmd->lst_out->file, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (*f < 0)
	{
		close(*f);
		if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
			return (rterf(lst_cmd->lst_out->file));
		return (rterp(lst_cmd->lst_out->file));
	}
	return (0);
}

int	open_redir2(t_lst_cmd *lst_cmd, struct stat *s)
{
	int		f;

	while (lst_cmd->lst_out->next)
	{
		stat(lst_cmd->lst_out->file, s);
		if (lst_cmd->lst_out->append == 0)
		{
			if (open_prev_fd(lst_cmd, s, &f) == -1)
				return (-1);
		}
		else
		{
			f = open(lst_cmd->lst_out->file, O_APPEND | O_RDWR | O_CREAT, 0644);
			if (f < 0)
			{
				close(f);
				if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
					return (rterf(lst_cmd->lst_out->file));
				return (rterp(lst_cmd->lst_out->file));
			}
		}
		close(f);
		lst_cmd->lst_out = lst_cmd->lst_out->next;
	}
	return (0);
}

int	open_redir3(t_lst_cmd	*lst_cmd, struct stat *s)
{
	stat(lst_cmd->lst_out->file, s);
	if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
	{
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (lst_cmd->fd_out < 0)
		{
			if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
				return (rterf(lst_cmd->lst_out->file));
			return (rterp(lst_cmd->lst_out->file));
		}
	}
	else
	{
		lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
				O_APPEND | O_RDWR | O_CREAT, 0644);
		if (lst_cmd->fd_out < 0)
		{
			if (!S_ISDIR(s->st_mode) && !S_ISREG(s->st_mode))
				return (rterf(lst_cmd->lst_out->file));
			return (rterp(lst_cmd->lst_out->file));
		}
	}
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
				return (rterf(lst_cmd->lst_in->file));
			return (rterp(lst_cmd->lst_in->file));
		}
	}
	return (0);
}
