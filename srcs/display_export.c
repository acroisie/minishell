/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:20:17 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/26 10:05:18 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_env(char **dest, t_minishell *data)
{
	char	*temp;
	int		i;

	i = -1;
	dest = ft_gc_calloc(ft_destlen(data->new_env), sizeof(char *));
	while (data->new_env[++i])
		dest[i] = ft_gc_strdup(data->new_env[i]);
	dest[i] = NULL;
	i = 0;
	while (dest[i])
	{
		if (dest[i + 1] == NULL)
			break ;
		if (ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			temp = ft_strdup(dest[i]);
			dest[i] = ft_strdup(dest[i + 1]);
			dest[i + 1] = ft_strdup(temp);
			i = 0;
		}
		else
			i++;
	}
	return (dest);
}

void	display_export(t_minishell *data)
{
	int		i;
	char	**split;
	char	*temp;
	char	**dest;

	dest = NULL;
	dest = sort_env(dest, data);
	i = -1;
	while (dest[++i])
	{
		if (ft_strchr(dest[i], '='))
		{
			split = ft_split(dest[i], '=');
			ft_gc_free(dest[i]);
			temp = ft_strjoin("=\"", split[1]);
			temp = ft_strjoin_free_s1(temp, "\"");
			temp = ft_strjoin_free_s2(split[0], temp);
			dest[i] = ft_strjoin_free_s2("declare -x ", temp);
		}
		else
			dest[i] = ft_strjoin_free_s2("declare -x ", dest[i]);
		ft_putendl_fd(dest[i], 1);
	}
	ft_free_split(split);
	ft_free_split(dest);
}
