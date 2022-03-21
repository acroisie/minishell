/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/21 09:41:05 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_lst_cmd *lst_cmd, t_minishell *data)
{
	char		*line;
	int			i;
	char		**prompt;
	char		*display;

	while (1)
	{
		i = 0;
		while (ft_strncmp(data->new_env[i], "PWD", 3))
			i++;
		prompt = ft_split(data->new_env[i], '/');
		i = 0;
		while (prompt[i])
			i++;
		display = ft_strjoin_free_s2("\033[1;92m", prompt[i - 1]);
		i = 0;
		display = ft_strjoin_free_s1(display, "> \033[0m");
		line = readline(display);
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			lst_cmd = ft_parse_args(line, data->new_env);
			print_lst(lst_cmd);
			data->start_cmd = lst_cmd;
			if (lst_cmd)
				exec_cmds(data, lst_cmd);
			lst_cmd = data->start_cmd;
			while (lst_cmd)
			{
				waitpid(lst_cmd->pid, NULL, 0);
				lst_cmd = lst_cmd->next;
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_lst_cmd	lst_cmd;
	t_minishell	data;

	if (argc != 1)
		return (0);
	if (!argv)
		return (0);
	if (!env)
		return (0);
	data.new_env = env;
	prompt(&lst_cmd, &data);
	return (0);
}
