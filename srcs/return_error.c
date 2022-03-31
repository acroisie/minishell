/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:30:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/30 19:53:17 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	return_error_builtin(char *cmd, char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb;
	if (strncmp(cmd, "cd", 2) != 0)
		exit(nb);
}

void	return_error(char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb;
}
