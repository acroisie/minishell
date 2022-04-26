/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/26 12:12:43 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert(char *line, char **env, t_var *var, t_ki ki)
{
	char	*end;

	end = ft_gc_strdup(&line[var->i]);
	var->i = (var->i - ki.i - 1);
	var->temp = ft_gc_strdup(line);
	var->temp[var->i] = '\0';
	var->temp = ft_strjoin(var->temp, &env[ki.k][ki.i + 1]);
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

void	ft_luther_le_bg(char *line, t_var *var)
{
	while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		var->i++;
}

void	ft_put_sign(char *line, t_var *var, char **env, int option)
{
	char	*temp;
	int		mem;
	t_ki	ki;

	ki.k = 0;
	mem = var->i;
	ft_luther_le_bg(line, var);
	temp = ft_strndup(&line[mem], (var->i - mem));
	ki.i = ft_strlen(temp);
	while (env[ki.k])
	{
		if (!ft_strncmp(env[ki.k], temp, ft_strlen(temp)))
		{
			if (env[ki.k][ft_strlen(temp)] == '=')
			{
				if (option)
					ft_insert(line, env, var, ki);
				else
					ft_write_string_output(ki.k, var, env, ft_strlen(temp));
				return ;
			}
		}
		ki.k++;
	}
	ft_gc_free(temp);
}

void	ft_dol_sign_process(char *line, t_var *var, char **env, int option)
{
	if (line[var->i + 1] == ' ' || line[var->i + 1] == '\0' \
	|| line[var->i + 1] == '|' || line[var->i + 1] == '/' \
	|| line[var->i + 1] == '"' || var->output == 3)
	{
		ft_write_char_output(line, var);
		return ;
	}
	var->i++;
	if (line[var->i] == '?')
	{
		ft_trigger_interrogation(var);
		return ;
	}
	ft_put_sign(line, var, env, option);
}
