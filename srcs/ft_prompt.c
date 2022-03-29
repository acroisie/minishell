/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:34:25 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/28 16:58:34 by lnemor           ###   ########lyon.fr   */
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
		free(prompt[i]);
	free(prompt);
	display = ft_strjoin_free_s1(display, "> \033[0m");
	line = readline(display);
	free(display);
	return (line);
}

void	execute_line(t_lst_cmd *lst_cmd, t_minishell *data, char *line)
{
	add_history(line);
	lst_cmd = ft_parse_args(line, data->new_env);
	free(line);
	print_lst(lst_cmd); // To delete
	data->start_cmd = lst_cmd;
	if (lst_cmd)
		exec_cmds(data, lst_cmd);
	lst_cmd = data->start_cmd;
	while (lst_cmd)
	{
		waitpid(lst_cmd->pid, NULL, 0);
		ft_free_split(lst_cmd->args);
		lst_cmd = lst_cmd->next;
	}
	free(lst_cmd);
}

void	prompt(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char		*line;
	int			i;
	char		**prompt;

	while (1)
	{
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
	}
}
