/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:24:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/23 20:39:08 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *data)
{
	int		i;
	char	*temp;
	char	**dest;

	i = 0;
	dest = data->new_env;
	while (dest[i] && dest[i + 1])
	{
		if (ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			temp = dest[i];
			dest[i] = dest[i + 1];
			dest[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	i = 0;
	while (dest[i])
	{
		ft_putendl_fd(dest[i], 1);
		i++;
	}
}
