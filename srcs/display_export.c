/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:20:17 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/25 18:21:12 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_env(char **dest)
{
	char	*temp;
	int		i;

	i = 0;
	while (dest[i] && dest[i + 1])
	{
		if (dest[i + 1] && ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			temp = dest[i];
			dest[i] = dest[i + 1];
			dest[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (dest);
}

void	display_export(char **dest)
{
	int		i;
	char	**split;
	char	*temp;
	char **sorted;

	i = -1;
	sorted = sort_env((dest));
	while (sorted[++i])
	{
		split = ft_split(sorted[i], '=');
		if (ft_strchr(sorted[i], '='))
		{
			ft_gc_free(sorted[i]);
			temp = ft_strjoin("=\"", split[1]);
			temp = ft_strjoin_free_s1(temp, "\"");
			temp = ft_strjoin_free_s2(split[0], temp);
			sorted[i] = ft_strjoin_free_s2("declare -x ", temp);
		}
		else
			sorted[i] = ft_strjoin_free_s2("declare -x ", sorted[i]);
		ft_putendl_fd(sorted[i], 1);
		ft_free_split(split);
	}
	ft_free_split(sorted);
}
