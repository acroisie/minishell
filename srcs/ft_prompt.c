/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:34:25 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/14 09:04:52 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*switch_display(char **prompt, char *line)
{
	char	*display;
	int		i;

	i = ft_destlen(prompt);
	display = ft_strjoin_free_s2("\033[1;92m", prompt[i - 1]);
	i = -1;
	while (prompt[++i + 1])
		ft_gc_free(prompt[i]);
	ft_gc_free(prompt);
	display = ft_strjoin_free_s1(display, "> \033[0m");
	line = readline(display);
	ft_gc_free(display);
	return (line);
}

void	execute_line(t_lst_cmd *lst_cmd, t_minishell *data, char *line)
{
	add_history(line);
	lst_cmd = ft_parse_args(line, data->new_env);
	ft_gc_free(line);
	data->start_cmd = lst_cmd;
	if (lst_cmd)
		exec_cmds(data, lst_cmd);
	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		waitpid(lst_cmd->pid, &g_rvalue, 0);
		if (WIFEXITED(g_rvalue))
			g_rvalue = WEXITSTATUS(g_rvalue);
		lst_cmd = lst_cmd->next;
	}
	ft_gc_destroy();
}

void	prompt(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char		*line;
	int			i;
	char		**prompt;

	while (1)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, ft_ctrl_bslash);
		i = -1;
		while (data->new_env[++i])
			if (ft_strncmp(data->new_env[i], "PWD", 3) == 0)
				break ;
		if (i != ft_destlen(data->new_env))
		{
			prompt = ft_split(data->new_env[i], '/');
			line = switch_display(prompt, line);
		}
		else
			line = readline("\033[1;92mminishel> \033[0m");
		if (ft_strlen(line) != 0)
			execute_line(lst_cmd, data, line);
		if (line)
			ft_gc_free(line);
		if (!line)
			the_noar2(0);
	}
}
