/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/17 11:27:13 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line)
{
	t_var		*var;

	var = ft_calloc(1, sizeof(t_var));
	ft_init_var(var);
	while (line[var->i])
	{
		if (line[var->i] == '|')
			ft_pipe_process(line, var);
		else if (line[var->i] == ' ')
			ft_space_process(line, var);
		else if (line[var->i] == '\'')
			ft_s_quotes_process(line, var);
		else if (line[var->i] == '"')
			ft_d_quotes_process(line, var);
		// else if (line[var->i] == '$')
		// 	ft_dollar_sign_process(line, var);
		else
			ft_copy_char(line, var);
	}
	while (var->lst_cmd->prev)
		var->lst_cmd = var->lst_cmd->prev;
	return (var->lst_cmd);
}

/*Todo_list:
- var.lst_cmd.args to double everytime when overflow 
or calculate size before run this part*/