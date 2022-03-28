/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:28:13 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/26 16:48:10 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_minishell *data, char **args)
{
	int		i;
	// char	*temp;

	i = 0;
	while (data->new_env[i])
	{
		if (ft_strncmp(args[1], data->new_env[i], ft_strlen(args[1])) == 0)
			break ;
		i++;
	}
	if (i == ft_destlen(data->new_env))
		exit(1);
	if (data->new_env[i])
	{
		// temp = data->new_env[i];
		data->new_env[i] = ft_strdup("");
	}
	return (0);
}
