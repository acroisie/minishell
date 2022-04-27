/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:32 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 13:26:46 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc2(t_lst_cmd *lst_cmd, pid_t pid, int fds[2])
{
	waitpid(pid, &g_rvalue, 0);
	if (WIFEXITED(g_rvalue))
		g_rvalue = WEXITSTATUS(g_rvalue);
	if (g_rvalue == 1)
		return (-1);
	close(fds[1]);
	lst_cmd->fd_in = fds[0];
	return (0);
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
	return (temp);
}

void	here_prompt(char *line, t_lst_cmd *lst_cmd, t_minishell *data,
	int *fds)
{
	char	*temp;

	while (1)
	{
		close(fds[0]);
		temp = NULL;
		line = readline("> ");
		if (!line)
			the_noar(line);
		line = dollar_here(line, data, temp);
		(void)data;
		if (ft_strcmp(line, lst_cmd->lst_herdoc->file) != 0)
			ft_putendl_fd(line, fds[1]);
		else if (ft_strncmp(line, lst_cmd->lst_herdoc->file,
				ft_strlen(line)) == 0)
			the_noar(line);
	}
}

int	ft_heredoc(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char	*line;
	pid_t	pid;
	int		fds[2];

	signal(SIGINT, ft_ctrl_c_h);
	signal(SIGQUIT, sig_exit);
	if (pipe(fds) == -1)
		exit (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_exit);
		signal(SIGQUIT, ft_ctrl_bslash);
		while (lst_cmd->lst_herdoc->next)
		{
			line = readline("> ");
			if (ft_strcmp(line, lst_cmd->lst_herdoc->file) == 0 || !line)
				lst_cmd->lst_herdoc = lst_cmd->lst_herdoc->next;
			free(line);
		}
		here_prompt(line, lst_cmd, data, fds);
	}
	else
		return (ft_heredoc2(lst_cmd, pid, fds));
	return (0);
}
