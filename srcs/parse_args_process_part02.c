/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:34:41 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/31 18:30:59 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				ft_write_string_output(k, var, env, 5);
				return ;
			}
		}
		k++;
	}
}

void	ft_set_ouput_in(t_var *var)
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

void	ft_set_ouput_out(char *line, t_var *var)
{
	if (!var->lst_cmd->lst_out)
	{
		var->lst_cmd->lst_out = ft_lstadd_tab(var->lst_cmd->lst_out, NULL);
		var->first_out = var->lst_cmd->lst_out;
		if (line[var->i + 1] == '>')
		{
			var->i++;
			var->lst_cmd->lst_out->append = 1;
		}
	}
	else
	{
		ft_lstadd_tab(var->lst_cmd->lst_out, NULL);
		var->lst_cmd->lst_out = var->lst_cmd->lst_out->next;
		if (line[var->i + 1] == '>')
		{
			var->i++;
			var->lst_cmd->lst_out->append = 1;
		}
	}
	var->output = 2;
}

void	ft_heredoc_process(t_var *var)
{
	if (!var->lst_cmd->lst_herdoc)
	{
		var->lst_cmd->lst_herdoc = ft_lstadd_tab(
				var->lst_cmd->lst_herdoc, NULL);
		var->first_here = var->lst_cmd->lst_herdoc;
	}
	else
	{
		ft_lstadd_tab(var->lst_cmd->lst_herdoc, NULL);
		var->lst_cmd->lst_herdoc = var->lst_cmd->lst_herdoc->next;
	}
	var->output = 3;
	var->i++;
}

void	ft_redir_process(char *line, t_var *var)
{
	if (line[var->i] == '<' && line[var->i + 1] != '<')
		ft_set_ouput_in(var);
	else if (line[var->i] == '>')
		ft_set_ouput_out(line, var);
	else if (line[var->i] == '<' && line[var->i + 1] == '<')
		ft_heredoc_process(var);
	var->i++;
	while (line[var->i] == ' ')
		var->i++;
}
