/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/22 21:16:18 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_lst_cmd	lst_cmd;
	t_minishell	data;
	int			i;

	if (argc != 1)
		return (0);
	if (!argv)
		return (0);
	if (!env)
		return (0);
	i = -1;
	data.new_env = ft_gc_calloc(sizeof(char *), ft_destlen(env));
	while (env[++i])
		data.new_env[i] = ft_gc_strdup(env[i]);
	data.new_env[i] = NULL;
	i = find_in_env(&data, "SHLVL");
	data.new_env = replace_exist_line_2(&data,
			data.new_env[i], data.new_env);
	i = -1;
	prompt(&lst_cmd, &data);
	return (0);
}

/* Todo_list: */

/* Error messages for builtin */
/* Signals dans heredoc */
