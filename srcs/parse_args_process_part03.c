/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part03.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:35:05 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/13 14:08:06 by lnemor           ###   ########lyon.fr   */
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
	var->lst_cmd->args[var->j] = ft_gc_calloc(1, sizeof(char));
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
	var->lst_cmd->args[var->j] = ft_gc_calloc(1, sizeof(char));
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
			ft_putendl_fd("unclosed quotes\n", 2);
			return ;
		}
		else
			ft_write_char_output(line, var);
	}
	var->i++;
}
