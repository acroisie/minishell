/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/05 11:45:02 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_process(char *line, t_var *var)
{
	var->i++;
	var->j = 0;
	ft_lstadd_cell(var->lst_cmd);
	while (line[var->i] == ' ')
		var->i++;
	var->lst_cmd = var->lst_cmd->next;
	var->lst_cmd->args[var->j] = ft_calloc(1, sizeof(char));
	var->lst_cmd->args[var->j][0] = '\0';
	var->output = 0;
}

void	ft_space_process(char *line, t_var *var)
{
	while (line[var->i] == ' ')
		var->i++;
	if (line[var->i] == '\0' || line[var->i] == '|'
		|| line[var->i] == '<' || line[var->i] == '>')
		return ;
	if (var->lst_cmd->args[var->j][0] != '\0')
		var->j++;
	var->lst_cmd->args[var->j] = ft_calloc(1, sizeof(char));
	var->lst_cmd->args[var->j][0] = '\0';
	var->output = 0;
}

void	ft_quotes_process(char *line, t_var *var, char **env)
{
	char	mem;

	mem = line[var->i];
	var->i++;
	while (line[var->i] != mem)
	{
		if (line[var->i] == '$' && mem == '"')
			ft_dol_sign_process(line, var, env, 0);
		else if (line[var->i] == '\0')
		{
			printf("unclosed quotes\n");
			return ;
		}
		else
			ft_write_char_output(line, var);
	}
	var->i++;
}

void	ft_insert(char *line, char **env, t_var *var, int k, int i)
{
	char	*end;

	end = ft_strdup(&line[var->i]);
	dprintf(1, "end; %s\n", end); //To delete
	var->i = (var->i - i - 1);
	line[var->i] = '\0';
	dprintf(1, "line1; %s\n", line); //To delete
	line = ft_strjoin(line, &env[k][i + 1]);
	dprintf(1, "line2; %s\n", line); //To delete
	line = ft_strjoin(line, end);
	dprintf(1, "line3; %s\n", line); //To delete
}

void	ft_dol_sign_process(char *line, t_var *var, char **env, int option)
{
	char	*temp;
	char	**rvalue;
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
		var->i++;
		rvalue = malloc(2 * sizeof (char *));
		rvalue[0] = ft_itoa(g_rvalue);
		ft_write_string_output(0, var, rvalue, -1);
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
				{
					// ft_insert(line, env, var, k, ft_strlen(temp)); // WIP
				}
				else
					ft_write_string_output(k, var, env, ft_strlen(temp));
				return ;
			}
		}
		k++;
	}
	free(temp);
}
