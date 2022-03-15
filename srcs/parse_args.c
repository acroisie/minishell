/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/15 17:43:03 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line)
{
	t_var		*var;

	var = malloc(sizeof(t_var) * 1);
	ft_init_var(var);
	while (line[var->i])
	{
		if (line[var->i] == ' ')
			ft_space_process(line, var);
		if (line[var->i] == '"')
			ft_d_quotes_process(line, var);
		else
		{
			var->lst_cmd->args[var->j] = ft_add_char(
					var->lst_cmd->args[var->j], line[var->i]);
			var->i++;
		}
	}
	return (var->lst_cmd);
}

/*Todo_list:
- var.lst_cmd.args to double everytime when overflow */