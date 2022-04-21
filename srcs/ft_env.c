/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:24:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/21 15:34:39 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *data)
{
	int		i;
	char	**dest;

	dest = data->new_env;
	i = 0;
	while (dest[i])
	{
		if (ft_strchr(dest[i], '='))
			ft_putendl_fd(dest[i], 1);
		i++;
	}
	exit(0);
}
