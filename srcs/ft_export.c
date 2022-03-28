/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/25 20:13:09 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(t_minishell *data, char **args)
{
	char	**dest;
	char	*temp;
	int		i;

	i = -1;
	dest = data->new_env;
	while (dest[++i] && dest[i + 1])
	{
		if (ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			temp = dest[i];
			dest[i] = dest[i + 1];
			dest[i + 1] = temp;
			i = -1;
		}
	}
	if (!args[1])
	{
		i = -1;
		while (dest[++i])
		{
			dest[i] = ft_strjoin("declare -x ", dest[i]);
			ft_putendl_fd(dest[i], 1);
		}
	}
	else
	{
		i = ft_destlen(data->new_env);
		data->new_env[i + 1] = args[1];
	}
	exit (0);
}
