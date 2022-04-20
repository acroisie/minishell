/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:32 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/20 13:18:15 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc2(t_lst_cmd *lst_cmd, pid_t pid, int fds[2])
{
	waitpid(pid, 0, 0);
	close(fds[1]);
	if (lst_cmd->lst_herdoc->next == NULL)
		lst_cmd->fd_in = fds[0];
	if (lst_cmd->lst_herdoc->next)
		close(fds[0]);
}

char	*join_temp(t_minishell *data, char *var_env, char *temp, int j)
{
	int		k;
	char	*var;

	temp = ft_gc_strdup("");
	k = 0;
	while (data->new_env[j][k] != '=')
		k++;
	var = ft_substr(data->new_env[j], k++,
			ft_strlen(data->new_env[j]));
	temp = ft_strjoin_free_s1(temp, var);
	ft_gc_free(var);
	ft_gc_free(var_env);
	return (temp);
}

char	*dollar_here(char *line, t_minishell *data, char *temp)
{
	char	*var_env;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (ft_isalnum(line[i++]) == 0)
				return (line);
			var_env = ft_gc_strdup("");
			while (ft_isalnum(line[i]) || line[i] == '_')
				var_env[j++] = line[i++];
			j = find_in_env(data, var_env);
			if (j <= ft_destlen(data->new_env))
				temp = join_temp(data, var_env, temp, j);
			i--;
		}
		else
			temp = ft_add_char(temp, line[i]);
	}
	free(line);
	return (temp);
}

void	here_prompt(char *line, t_lst_cmd *lst_cmd, t_minishell *data,
	int fds[2])
{
	char	*temp;

	temp = NULL;
	line = dollar_here(line, data, temp);
	if (ft_strcmp(line, lst_cmd->lst_herdoc->file) != 0)
		ft_putendl_fd(line, fds[1]);
	if (ft_strcmp(line, lst_cmd->lst_herdoc->file) == 0)
		the_noar(line);
}

int	ft_heredoc(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char	*line;
	pid_t	pid;
	int		fds[2];

	if (pipe(fds) == -1)
		exit (-1);
	pid = fork();
	signal(SIGQUIT, ft_ctrl_c_h);
	signal(SIGINT, sig_put_endl);
	if (pid == 0)
	{
		signal(SIGINT, ft_ctrl_c_h);
		signal(SIGQUIT, ft_ctrl_bslash);
		close(fds[0]);
		while (1)
		{
			line = readline("> ");
			here_prompt(line, lst_cmd, data, fds);
		}
	}
	else
		ft_heredoc2(lst_cmd, pid, fds);
	return (0);
}
