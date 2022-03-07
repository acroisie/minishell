/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/07 15:33:19 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_lst_cmd	*lst_cmd;
	t_minishell	data;
	int	i;

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
			if (lst_cmd->args && lst_cmd->args[0])
			{
				exec_cmds(&data, lst_cmd);
				i = 0;
				print_lst(lst_cmd);
				while (lst_cmd)
				{
					waitpid(lst_cmd->pid, 0, 0);
					dprintf(2, "waited cmd %d\n", i);
					lst_cmd = lst_cmd->next;
				}
			}
		}
	}
	
	return (0);
}
