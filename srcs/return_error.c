/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:30:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/21 14:33:38 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	return_error_builtin(char *cmd, char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb % 256;
	if (ft_strncmp(cmd, "cd", 2) != 0)
		exit(nb % 256);
}

void	return_error_exit(char *cmd, char *arg, char *msg, int nb)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb % 256;
	exit (nb % 256);
}

int	return_error_export(char *cmd, char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb % 256;
	return (-1);
}

void	return_error(char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb % 256;
	return ;
}

void	return_error_2(char *arg, char *msg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(msg, 2);
	g_rvalue = nb % 256;
	exit(nb % 256);
}
