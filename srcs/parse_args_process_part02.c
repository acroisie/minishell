/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:41 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/24 15:11:27 by acroisie         ###   ########lyon.fr   */
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
				// var->lst_cmd->args[var->j] = ft_strjoin_free_s1(
				// 		var->lst_cmd->args[var->j],
				// 		&env[k][5]);
				ft_write_string_output(k, var, env);
				return ;
			}
		}
		k++;
	}
}

void	ft_redir_process(char *line, t_var *var, char **env)
{
	char	mem;

	if (line[var->i] == '<')
		mem = 1;
	else
		mem = 2;
	var->i++;
	if (line[var->i] == line[var->i - 1])
	{
		
	}
		if (mem == 1)
			printf("Heredoc\n");    // To delete
		else
			printf("Add line to\n");    // To delete
	while (line[var->i == ' '])
		var->i++;
	while (line[var->i] != ' ' || line[var->i] != '\0' || line[var->i] != '|')
	{
		if (line[var->i] == '\'')
			ft_s_quotes_process(line, var);
		else if (line[var->i] == '"')
			ft_d_quotes_process(line, var, env);
		else if (line[var->i] == '$')
			ft_dol_sign_process(line, var, env, 1);
		else if (line[var->i] == '~')
			ft_tilde_process(var, env);
	}
}
