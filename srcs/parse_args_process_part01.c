/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/29 19:17:36 by acroisie         ###   ########lyon.fr   */
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

void	ft_s_quotes_process(char *line, t_var *var)
{
	var->i++;
	while (line[var->i] != '\'')
	{
		if (line[var->i] == '\0') // Modify to make a clean end
		{
			printf("unclosed quotes\n");
			exit (1);
		}
		else
			ft_write_char_output(line, var);
	}
	var->i++;
}

/* Do a specific case for echo $?*/

void	ft_d_quotes_process(char *line, t_var *var, char **env)
{
	var->i++;
	while (line[var->i] != '"')
	{
		if (line[var->i] == '$')
			ft_dol_sign_process(line, var, env, 0);
		else if (line[var->i] == '\0') // Modify to make a clean end
		{
			printf("unclosed quotes\n");
			exit (1);
		}
		else
			ft_write_char_output(line, var);
	}
	var->i++;
}

void	ft_dol_sign_process(char *line, t_var *var, char **env, int option)
{
	char	*temp;
	int		mem;
	int		k;

	var->i++;
	mem = var->i;
	k = 0;
	if (line[var->i] == ' ' || line[var->i] == '\0' || line[var->i] == '|')
	{
		var->lst_cmd->args[var->j] = ft_add_char(
				var->lst_cmd->args[var->j], '$');
		return ;
	}
	while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		var->i++;
	temp = ft_strndup(&line[mem], (var->i - mem));
	while (env[k])
	{
		if (!ft_strncmp(env[k], temp, ft_strlen(temp) - 1))
		{
			if (env[k][ft_strlen(temp)] == '=')
			{
				ft_write_string_output(k, var, env);
				if (option)
					// printf("Do different stuff \n");
				return ;
			}
		}
		k++;
	}
	free(temp);
}
