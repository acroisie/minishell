/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/07 18:00:54 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_lst_cmd	*lst_cmd;
	t_minishell	data;

	if (argc != 1)
		return (0);
	if (!argv)
		return (0);
	data.new_env = env;
	while (1)
	{
		line = readline("\033[1;92mminishell> \033[0m");
		if (line)
		{
			add_history(line);
			lst_cmd = ft_parse_args(line);
			data.start_cmd = lst_cmd;
			if (lst_cmd)
			{
				exec_cmds(&data, lst_cmd);
			}
			lst_cmd = data.start_cmd;
			while (lst_cmd)
			{
				waitpid(lst_cmd->pid, NULL, 0);
				lst_cmd = lst_cmd->next;
			}
		}
	}
	return (0);
}
