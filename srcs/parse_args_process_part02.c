/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:41 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/29 19:21:17 by acroisie         ###   ########lyon.fr   */
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
	if (line[var->i] == '<' && line[var->i + 1] == '<')
	{
		if (!var->lst_cmd->lst_herdoc)
		{
			var->lst_cmd->lst_herdoc = ft_lstadd_tab(
					var->lst_cmd->lst_herdoc, NULL);
			var->first_out = var->lst_cmd->lst_herdoc;
		}
		else
		{
			ft_lstadd_tab(var->lst_cmd->lst_herdoc, NULL);
			var->lst_cmd->lst_herdoc = var->lst_cmd->lst_herdoc->next;
		}
		var->output = 3;
		var->i++;
	}
	else if (line[var->i] == '<')
	{
		if (!var->lst_cmd->lst_in)
		{
			var->lst_cmd->lst_in = ft_lstadd_tab(var->lst_cmd->lst_in, NULL);
			var->first_in = var->lst_cmd->lst_in;
		}
		else
		{
			ft_lstadd_tab(var->lst_cmd->lst_in, NULL);
			var->lst_cmd->lst_in = var->lst_cmd->lst_in->next;
		}
		var->output = 1;
	}
	else if (line[var->i] == '>')
	{
		/* la partie pour le appen c'est le bail 
		juste en dessous BG*/
		
		// if (line[var->i + 1] == '>')
		// {
		// 	var->i++;
		// 	var->lst_cmd->lst_out->append = 1;
		// }
		if (!var->lst_cmd->lst_out)
		{
			var->lst_cmd->lst_out = ft_lstadd_tab(var->lst_cmd->lst_out, NULL);
			var->first_out = var->lst_cmd->lst_out;
		}
		else
		{
			ft_lstadd_tab(var->lst_cmd->lst_out, NULL);
			var->lst_cmd->lst_out = var->lst_cmd->lst_out->next;
		}
		var->output = 2;
	}
	var->i++;
	while (line[var->i] == ' ')
		var->i++;
}
