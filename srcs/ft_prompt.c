/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:34:25 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/20 13:19:51 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*switch_display(char **prompt, char *line)
{
	char	*display;
	int		i;

	i = ft_destlen(prompt);
	display = ft_strjoin_free_s2("", prompt[i - 1]);
	i = -1;
	while (prompt[++i + 1])
		ft_gc_free(prompt[i]);
	ft_gc_free(prompt);
	display = ft_strjoin_free_s1(display, "> ");
	line = readline(display);
	ft_gc_free(display);
	return (line);
}

void	execute_line(t_lst_cmd *lst_cmd, t_minishell *data, char *line)
{
	add_history(line);
	lst_cmd = ft_parse_args(line, data->new_env);
	free(line);
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
	ft_gc_free(lst_cmd);
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
		i = find_in_env(data, "PWD");
		if (i != ft_destlen(data->new_env))
		{
			prompt = ft_split(data->new_env[i], '/');
			line = switch_display(prompt, line);
		}
		else
			line = readline("minishell> ");
		if (ft_strlen(line) != 0)
			execute_line(lst_cmd, data, line);
		else if (line)
			free(line);
		if (!line)
			the_noar2(0);
	}
}
