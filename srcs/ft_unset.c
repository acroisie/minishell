/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:28:13 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/12 11:25:07 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_minishell *data, char **args)
{
	int		i;

	i = 0;
	while (data->new_env[i])
	{
		if (ft_strncmp(args[1], data->new_env[i], ft_strlen(args[1])) == 0)
			break ;
		i++;
	}
	if (i == ft_destlen(data->new_env))
		exit(0);
	if (data->new_env[i])
		data->new_env[i] = ft_strdup("");
	return (0);
}
