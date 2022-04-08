/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/08 10:00:36 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_double_array(t_var *var)
{
	int		i;
	char	**temp;

	i = 0;
	var->tab_size = (var->tab_size * 2) + var->tab_size;
	temp = ft_calloc(var->tab_size, sizeof(char *));
	while (var->lst_cmd->args[i])
	{
		temp[i] = ft_strdup(var->lst_cmd->args[i]);
		free(var->lst_cmd->args[i]);
		i++;
	}
	return (temp);
}

void	ft_set_first_link(t_var *var)
{
	while (var->lst_cmd->prev)
		var->lst_cmd = var->lst_cmd->prev;
	var->lst_cmd->lst_out = var->first_out;
	var->lst_cmd->lst_in = var->first_in;
	var->lst_cmd->lst_herdoc = var->first_here;
}

t_lst_cmd	*ft_parse_args(char *line, char **env)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	ft_init_var(var);
	while (line[var->i])
	{
		if (line[var->i] == '|')
			ft_pipe_process(line, var);
		else if (line[var->i] == ' ')
		{
			// if (var->j >= var->tab_size - 1)
			// 	var->lst_cmd->args = ft_double_array(var);
			ft_space_process(line, var);
		}
		else if (line[var->i] == '\'' || line[var->i] == '"')
			ft_quotes_process(line, var, env);
		else if (line[var->i] == '$')
			ft_dol_sign_process(line, var, env, 1);
		else if (line[var->i] == '~')
			ft_tilde_process(var, env);
		else if (line[var->i] == '<' || line[var->i] == '>')
			ft_redir_process(line, var);
		else
			ft_write_char_output(line, var);
	}
	ft_set_first_link(var);
	return (var->lst_cmd);
}
