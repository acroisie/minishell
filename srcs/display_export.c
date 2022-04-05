/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:20:17 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/05 13:48:04 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_env(char **dest)
{
	char	*temp;
	int		i;

	i = -1;
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
	return (dest);
}

void	display_export(char **dest)
{
	int	i;

	i = -1;
	dest = sort_env(dest);
	while (dest[++i])
	{
		dest[i] = ft_strjoin_free_s2("declare -x ", dest[i]);
		ft_putendl_fd(dest[i], 1);
	}
	i = -1;
	while (dest[++i])
		free(dest[i]);
	free(dest);
}
