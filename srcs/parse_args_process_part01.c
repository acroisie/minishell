/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process_part01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/16 09:38:37 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_space_process(char *line, t_var *var)
{
	var->j++;
	while (line[var->i] == ' ')
		var->i++;
	var->lst_cmd->args[var->j] = malloc(1 * sizeof(char));
	var->lst_cmd->args[var->j][0] = '\0';
}

void	ft_s_quotes_process(char *line, t_var *var)
{
	var->i++;
	while (line[var->i] != '\'')
	{
		if (line[var->i] == '\0') // Modify when Luther's back.
		{
			printf("unclosed quotes\n");
			exit (1);
		}
		var->lst_cmd->args[var->j] = ft_add_char(
				var->lst_cmd->args[var->j], line[var->i]);
		var->i++;
	}
	var->i++;
}

void	ft_d_quotes_process(char *line, t_var *var)
{
	var->i++;
	while (line[var->i] != '"')
	{
		if (line[var->i] == '\0') // Modify when Luther's back.
		{
			printf("unclosed quotes\n");
			exit (1);
		}
		var->lst_cmd->args[var->j] = ft_add_char(
				var->lst_cmd->args[var->j], line[var->i]);
		var->i++;
	}
	var->i++;
}

// void	ft_dollar_sign_process(char *line, t_var var)
// {
// 	var->i++;
// }
