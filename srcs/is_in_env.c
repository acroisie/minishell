/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:46:29 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/22 00:07:47 by lnemor           ###   ########lyon.fr   */
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
		if (!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0])))
		{
			ft_free_split(split);
			return (1);
		}
		i++;
	}
	ft_free_split(split);
	return (0);
}