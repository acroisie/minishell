/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/28 10:49:23 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	open_redir(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->lst_in != NULL)
	{
		lst_cmd->fd_in = open(ft_lstlast_tab(lst_cmd->lst_in)->file, O_RDONLY);
		if (lst_cmd->fd_in < 0)
			return_error(lst_cmd->lst_out->file, ": Permission denied", 1);
	}
	if (lst_cmd->lst_out != NULL)
	{
		open_redir2(lst_cmd);
		if (ft_lstlast_tab(lst_cmd->lst_out)->append == 0)
		{
			lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
					O_TRUNC | O_RDWR | O_CREAT, 0644);
			if (lst_cmd->fd_out < 0)
				return_error(lst_cmd->lst_out->file, ": Permission denied", 1);
		}
		else
		{
			lst_cmd->fd_out = open(ft_lstlast_tab(lst_cmd->lst_out)->file,
					O_APPEND | O_RDWR | O_CREAT, 0644);
			if (lst_cmd->fd_out < 0)
				return_error(lst_cmd->lst_out->file, ": Permission denied", 1);
		}
	}
}

void	the_noar(char	*line)
{
	free(line);
	exit(0);
}

void	ft_heredoc2(t_lst_cmd *lst_cmd, pid_t pid, int fds[2])
{
	waitpid(pid, 0, 0);
	close(fds[1]);
	if (lst_cmd->lst_herdoc->next == NULL)
		lst_cmd->fd_in = fds[0];
	if (lst_cmd->lst_herdoc->next)
		close(fds[0]);
	close(fds[0]);
}

void	ft_dollar_sign_process(char *line, t_var *var, char **env)
{
	char	*temp;
	int		mem;
	int		k;

	var->i++;
	mem = var->i;
	k = 0;
	if (line[var->i] == ' ' || line[var->i] == '\0' || line[var->i] == '|')
	{
		var->lst_cmd->args[var->j] = ft_add_char(
				var->lst_cmd->args[var->j], '$');
		return ;
	}
	while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		var->i++;
	temp = ft_strndup(&line[mem], (var->i - mem));
	while (env[k])
	{
		if (!ft_strncmp(env[k], temp, ft_strlen(temp) - 1))
		{
			if (env[k][ft_strlen(temp)] == '=')
			{
				var->lst_cmd->args[var->j] = ft_strjoin(
						var->lst_cmd->args[var->j],
						&env[k][ft_strlen(temp) + 1]);
				return ;
			}
		}
		k++;
	}
	free(temp);
}

int	ft_heredoc(t_lst_cmd *lst_cmd)
{
	char	*line;
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		while (1)
		{
			line = readline(">");
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) != 0)
				ft_putendl_fd(line, fds[1]);
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) == 0)
				the_noar(line);
			free(line);
		}
	}
	else
		ft_heredoc2(lst_cmd, pid, fds);
	return (0);
}
