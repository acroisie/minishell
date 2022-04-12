/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/12 09:16:25 by acroisie         ###   ########lyon.fr   */
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
		data.new_env[i] = ft_strdup(env[i]);
	data.new_env[i] = NULL;
	i = -1;
	prompt(&lst_cmd, &data);
	return (0);
}

/* Todo_list: */

/* Fix leaks */
/* Error messages for builtin */
/* Exit builtins */
/* Signals */
/* Norm */