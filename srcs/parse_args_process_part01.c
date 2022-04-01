/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/01 09:46:05 by acroisie         ###   ########lyon.fr   */
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
	while (ft_isalnum(line[var->i]) || line[var->i] == '_')
		var->i++;
	temp = ft_strndup(&line[mem], (var->i - mem));
	while (env[k])
	{
		dprintf(1, "%c\n", env[k][ft_strlen(temp) - 1]); // To delete
		if (!ft_strncmp(env[k], temp, ft_strlen(temp) - 1))
		{
			if (env[k][ft_strlen(temp)] == '=')
			{
				ft_write_string_output(k, var, env, mem);
				if (option)
					// printf("Do different stuff \n");
				return ;
			}
		}
		k++;
	}
	free(temp);
}
