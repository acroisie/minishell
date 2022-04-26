/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:24:41 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/25 15:33:13 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *data)
{
	int		i;
	char	**dest;

	i = -1;
	dest = ft_gc_calloc(sizeof(char *), ft_destlen(data->new_env) + 1);
	while (data->new_env[++i])
		dest[i] = ft_gc_strdup(data->new_env[i]);
	dest[i] = NULL;
	i = 0;
	while (dest[i])
	{
		if (ft_strchr(dest[i], '='))
			ft_putendl_fd(dest[i], 1);
		i++;
	}
	exit(0);
}
