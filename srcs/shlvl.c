/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:31:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/22 00:32:05 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**replace_exist_line_2(t_minishell *data, char *args, char **dest)
{
	char	**split;
	int		i;
	char	*temp;
	int		shlvl;

	i = -1;
	temp = ft_gc_strdup(args);
	split = ft_split(temp, '=');
	shlvl = ft_atoi(split[1]) + 1;
	temp = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	while (data->new_env[++i] != NULL)
	{
		if (!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0])))
			break ;
	}
	if (i != ft_destlen(data->new_env) && !ft_strncmp(data->new_env[i],
			split[0], ft_strlen(split[0])))
		dest[i] = ft_gc_strdup(temp);
	else
		dest = ft_addline(dest, temp);
	ft_free_split(split);
	return (dest);
}
