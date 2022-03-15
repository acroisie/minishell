/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:56 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/15 14:27:20 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_space_process(char *line, t_var *var)
{
	var->j++;
	var->lst_cmd->args[var->j] == malloc(1 * sizeof(char));
	var->lst_cmd->args[var->j][0] == '\0';
}

void	ft_d_quotes_process(char *line, t_var *var)
{
	var->i++;
	while (line[var->i] != '"')
	{
		var->lst_cmd->args[var->j] = ft_add_char(
				var->lst_cmd->args[var->j], line[var->i]);
		var->i++;
	}
	var->i++;
}