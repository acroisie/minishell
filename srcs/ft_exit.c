/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:57:55 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 11:10:03 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	the_noar_exit(unsigned int nb)
{
	g_rvalue = nb;
	ft_gc_destroy();
	exit(nb % 256);
}

void	the_noar2(unsigned int nb)
{
	ft_putendl_fd("exit", 2);
	g_rvalue = nb;
	ft_gc_destroy();
	exit(nb % 256);
}

void	check_args(t_lst_cmd *lst_cmd, int i, int j)
{
	if (i > 1)
		return (return_error_exit("exit: ", "", " too many arguments", 1));
	while (lst_cmd->args[i][j] == ' ')
		j++;
	if (lst_cmd->args[i][j] == '-' || lst_cmd->args[i][j] == '+')
		j++;
	while (ft_isdigit(lst_cmd->args[i][j]))
		j++;
	if (!lst_cmd->args[i][j])
		return ;
	if (!ft_isdigit(lst_cmd->args[i][j]) && lst_cmd->args[i][j] != ' ')
		return_error_exit("exit: ", lst_cmd->args[1],
			": numeric argument required", 255);
	while (lst_cmd->args[i][j] == ' ')
		j++;
	if (lst_cmd->args[i][j] != ' ' && lst_cmd->args[i][j])
		return_error_exit("exit: ", lst_cmd->args[1],
			": numeric argument required", 255);
}

void	ft_exit(t_lst_cmd *lst_cmd)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!lst_cmd->prev && !lst_cmd->next)
		ft_putendl_fd("exit", 2);
	while (lst_cmd->args[++i])
		check_args(lst_cmd, i, j);
	if (lst_cmd->args[1])
		the_noar_exit(ft_atol(lst_cmd->args[1]));
	the_noar_exit(g_rvalue);
}
