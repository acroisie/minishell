/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:19:37 by acroisie          #+#    #+#             */
/*   Updated: 2021/11/03 09:19:37 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_value(int sign)
{
	if (sign >= 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(char const *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 3 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		if ((result > 2147483647 && sign >= 0)
			|| (result > 2147483648 && sign < 0))
			return (return_value(sign));
	}
	return (result * sign);
}

static int	return_error_atol(char *cmd, char *arg, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (nb);
}

unsigned int	ft_atol(char const *str)
{
	int				i;
	int				sign;
	long long int	result;
	int				overflow;

	i = 0;
	sign = 1;
	result = 0;
	overflow = 1;
	while ((str[i] >= 3 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		if (result < 0 && sign == 1)
			overflow = -1;
		if (result < 0 && sign == -1)
			overflow = 0;
	}
	if (overflow == 1)
		return (result * sign);
	return (return_error_atol("exit: ", (char *)str, 255));
}
