/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:39 by acroisie          #+#    #+#             */
/*   Updated: 2022/04/06 11:25:14 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_flag(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (arg[i] == '-')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] == 'n')
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = ft_flag(args[i]);
	if (flag)
		while (ft_flag(args[i]))
			i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
