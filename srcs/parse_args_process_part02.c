/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:41 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/23 15:45:45 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_copy_char(char *line, t_var *var)
{
	var->lst_cmd->args[var->j] = ft_add_char(
			var->lst_cmd->args[var->j], line[var->i]);
	var->i++;
}

void	ft_tilde_process(t_var *var, char **env)
{
	int		k;

	var->i++;
	k = 0;
	while (env[k])
	{
		if (!ft_strncmp(env[k], "HOME", 3))
		{
			if (env[k][4] == '=')
			{
				var->lst_cmd->args[var->j] = ft_strjoin(
						var->lst_cmd->args[var->j],
						&env[k][5]);
				return ;
			}
		}
		k++;
	}
}

// void	ft_redir_process(char *line, t_var *var, char **env)
// {
// 	char	mem;

// 	if (line[var->i] == '<')
// 		mem = 1;
// 	else
// 		mem = 2;
// 	var->i++;
// 	if (line[var->i] == line[var->i - 1])
// 		if (mem == 1)
// 			printf("Heredoc\n");    // To delete
// 		else
// 			printf("Add line to\n");    // To delete
// }
