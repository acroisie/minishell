/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:46 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/24 14:27:41 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_lst_cmd	lst_cmd;
	t_minishell	data;

	if (argc != 1)
		return (0);
	if (!argv)
		return (0);
	if (!env)
		return (0);
	data.new_env = malloc(sizeof(char *) * ft_destlen(env) + 1);
	data.new_env = env;
	prompt(&lst_cmd, &data);
	return (0);
}
