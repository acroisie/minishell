/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:57:55 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/31 19:17:39 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	the_noar2(unsigned int nb)
{
	ft_putendl_fd("exit", 2);
	g_rvalue = nb;
	exit(nb % 256);
}

void	ft_exit(t_lst_cmd *lst_cmd)
{
	int				i;
	int				j;

	i = 0;
	j = -1;
	while (lst_cmd->args[++i])
	{
		if (i > 1)
		{
			g_rvalue = 1;
			return (ft_putendl_fd("bash: exit: too many arguments", 2));
		}
		if (lst_cmd->args[i][0] == '-' || lst_cmd->args[i][0] == '+')
			j++;
		while (lst_cmd->args[i][++j])
			if (ft_isdigit(lst_cmd->args[i][j]) == 0)
				return_error_exit("exit: ", lst_cmd->args[1],
					": numeric argument required", -1);
	}
	if (i <= 2)
	{
		if (lst_cmd->args[1])
			the_noar2(ft_atol(lst_cmd->args[1]));
		the_noar2(0);
	}
}
