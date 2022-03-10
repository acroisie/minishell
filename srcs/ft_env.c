/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:24:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/10 16:03:25 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *data)
{
	int	i;

	i = 0;
	while (data->new_env[i])
	{
		ft_putendl_fd(data->new_env[i], 1);
		i++;
	}
}
