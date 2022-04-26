/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:46:29 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/26 16:40:31 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_env(t_minishell *data, char *arg)
{
	int		i;
	char	**split;

	split = ft_split(arg, '=');
	i = 0;
	while (data->new_env[i])
	{
		if (!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0])) \
		&& data->new_env[i][ft_strlen(split[0])] == '=')
		{
			ft_free_split(split);
			return (1);
		}
		i++;
	}
	ft_free_split(split);
	return (0);
}
