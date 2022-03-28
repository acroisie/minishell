/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:41 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/28 15:10:37 by acroisie         ###   ########lyon.fr   */
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
				ft_write_string_output(k, var, env);
				return ;
			}
		}
		k++;
	}
}

void	ft_redir_process(char *line, t_var *var)
{
	if (line[var->i] == '<')
	{
		if (!var->lst_cmd->lst_in)
			var->lst_cmd->lst_in = ft_create_tab(NULL);
		else
			ft_lstadd_tab(var->lst_cmd->lst_in, var->lst_cmd->lst_in->file);
		var->lst_cmd->lst_in->file = ft_calloc(1, sizeof(char) * 1);
		var->lst_cmd->lst_in->file[0] = '\0';
		var->output = 1;
	}
	if (line[var->i] == '>')
	{
		if (!var->lst_cmd->lst_in)
			var->lst_cmd->lst_out = ft_create_tab(NULL);
		else
			ft_lstadd_tab(var->lst_cmd->lst_out, var->lst_cmd->lst_out->file);
		var->lst_cmd->lst_out->file = ft_calloc(1, sizeof(char) * 1);
		var->lst_cmd->lst_out->file[0] = '\0';
		var->output = 2;
	}
	var->i++;
	while (line[var->i] == ' ')
		var->i++;
}
