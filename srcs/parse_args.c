/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/29 18:31:24 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lst_cmd	*ft_parse_args(char *line, char **env)
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
			ft_d_quotes_process(line, var, env);
		else if (line[var->i] == '$')
			ft_dol_sign_process(line, var, env, 1);
		else if (line[var->i] == '~')
			ft_tilde_process(var, env);
		else if (line[var->i] == '<' || line[var->i] == '>')
			ft_redir_process(line, var);
		else
			ft_write_char_output(line, var);
	}
	while (var->lst_cmd->prev)
		var->lst_cmd = var->lst_cmd->prev;
	var->lst_cmd->lst_out = var->first_out;
	var->lst_cmd->lst_in = var->first_in;
	var->lst_cmd->lst_herdoc = var->first_here;
	return (var->lst_cmd);
}

/*Todo_list:
- var.lst_cmd.args to double everytime when overflow 
or calculate size before run this part*/