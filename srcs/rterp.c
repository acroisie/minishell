/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rterp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:23:45 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/28 14:25:05 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	rterp(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_rvalue = 1;
	return (-1);
}

int	rterf(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_rvalue = 1;
	return (-1);
}
