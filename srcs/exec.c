/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:51 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/18 17:31:30 by lnemor           ###   ########lyon.fr   */
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
		init_dup(lst_cmd);
		if (find_path(data, lst_cmd->args[0]) == 0
			&& lst_cmd->args[0][0] != '/' && is_builtin(lst_cmd) == 0)
		{
			ft_putstr_fd("command not found\n", 2);
			exit (0);
		}
		if (is_builtin(lst_cmd) == 0)
		{
			if (lst_cmd->args[0][0] == '/')
				execve(lst_cmd->args[0], lst_cmd->args, data->new_env);
			else
				lst_cmd->path = find_path(data, lst_cmd->args[0]);
			if (execve(lst_cmd->path, lst_cmd->args, data->new_env) == -1)
				exit(1);
		}
		if (is_builtin(lst_cmd) == 1)
			do_builtin(data, lst_cmd);
	}
	return ;
}
int		heredoc(t_lst_cmd *t_lst_cmd)
{
	
}

void	exec_cmds(t_minishell *data, t_lst_cmd *lst_cmd)
{
	char	*line;

	lst_cmd = data->start_cmd;
	lst_cmd->lst_herdoc = ft_create_tab("test");
	lst_cmd->lst_herdoc->next = ft_create_tab("test2");
	while (lst_cmd)
	{
		open_redir(lst_cmd);
		if (lst_cmd->lst_herdoc != NULL)
		{
			while (strncmp(line, lst_cmd->lst_herdoc->file,
					ft_strlencustom(lst_cmd->lst_herdoc->file)) != 0)
				line = readline(">");
			dprintf(2, "debug\n");
			lst_cmd->lst_herdoc = lst_cmd->lst_herdoc->next;
		}
		if (lst_cmd->next != NULL)
			pipe(lst_cmd->pipe_fd);
		ft_fork(lst_cmd, data);
		if (lst_cmd->prev != NULL)
			close(lst_cmd->prev->pipe_fd[0]);
		if (lst_cmd->next != NULL)
			close(lst_cmd->pipe_fd[1]);
		if (lst_cmd->fd_in != 0)
			close(lst_cmd->fd_in);
		if (lst_cmd->fd_out != 0)
			close(lst_cmd->fd_out);
		lst_cmd = lst_cmd->next;
	}
	lst_cmd = data->start_cmd;
}
