/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:20:33 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/05 14:48:20 by lnemor           ###   ########lyon.fr   */
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
}

char	*dollar_here(char *line, t_minishell *data)
{
	char	*temp;
	char	*var_env;
	char	*var;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	var_env = ft_strdup("");
	temp = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (ft_isalnum(line[i++]) == 0)
				return (line);
			while (ft_isalnum(line[i]) || line[i] == '_')
				var_env[j++] = line[i++];
			j = -1;
			while (data->new_env[++j])
				if (!ft_strncmp(data->new_env[j], var_env, ft_strlen(var_env)))
					break ;
			if (j <= ft_destlen(data->new_env))
			{
				while (data->new_env[j][k] != '=')
					k++;
				var = ft_substr(data->new_env[j], k++,
						ft_strlen(data->new_env[j]));
				temp = ft_strjoin_free_s1(temp, var);
				free(var_env);
				free(var);
			}
			i--;
		}
		else
			temp = ft_add_char(temp, line[i]);
	}
	return (temp);
}

int	ft_heredoc(t_lst_cmd *lst_cmd, t_minishell *data)
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
			line = readline("> ");
			line = dollar_here(line, data);
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) != 0)
				ft_putendl_fd(line, fds[1]);
			dprintf(2, "list {%s} | line : {%s}\n", lst_cmd->lst_herdoc->file, line);
			dprintf(2, "comp %i \n", ft_strcmp(line, lst_cmd->lst_herdoc->file));
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) == 0)
			{
				dprintf(2, "caca \n");
				the_noar(line);
			}
			free(line);
		}
	}
	else
		ft_heredoc2(lst_cmd, pid, fds);
	return (0);
}
