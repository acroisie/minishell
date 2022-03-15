/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/15 15:08:22 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line)
{
	t_var		*var;

	ft_init_var(var);
	while (line[var->i])
	{
		if (line[var->i] == ' ')
			ft_space_process(line, var);
		if (line[var->i] == '"')
			ft_d_quotes_process(line, var);
		else
		{
			var->temp[var->j] = ft_add_char(var->temp[var->j], line);
			var->i++;
		}
	}
	return (var->lst_cmd);
}
