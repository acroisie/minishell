/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/12 10:52:06 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert(char *line, char **env, t_var *var, int k, int i)
{
	char	*end;

	end = ft_strdup(&line[var->i]);
	var->i = (var->i - i - 1);
	var->temp = ft_strdup(line);
	var->temp[var->i] = '\0';
	var->temp = ft_strjoin(var->temp, &env[k][i + 1]);
	var->temp = ft_strjoin(var->temp, end);
}

void	ft_trigger_interrogation(t_var *var)
{
	char	**rvalue;

	var->i++;
	rvalue = ft_gc_calloc(2, sizeof (char *));
	rvalue[0] = ft_itoa(g_rvalue);
	ft_write_string_output(0, var, rvalue, -1);
}

void	ft_dol_sign_process(char *line, t_var *var, char **env, int option)
{
	char	*temp;
	int		mem;
	int		k;

	k = 0;
	if (line[var->i + 1] == ' ' || line[var->i + 1] == '\0'
		|| line[var->i + 1] == '|')
	{
		ft_write_char_output(line, var);
		var->i++;
		return ;
	}
	var->i++;
	mem = var->i;
	if (line[var->i] == '?')
	{
		ft_trigger_interrogation(var);
		return ;
	}
	while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		var->i++;
	temp = ft_strndup(&line[mem], (var->i - mem));
	while (env[k])
	{
		if (!ft_strncmp(env[k], temp, ft_strlen(temp)))
		{
			if (env[k][ft_strlen(temp)] == '=')
			{
				if (option)
					ft_insert(line, env, var, k, ft_strlen(temp));
				else
					ft_write_string_output(k, var, env, ft_strlen(temp));
				return ;
			}
		}
		k++;
	}
	free(temp);
}
