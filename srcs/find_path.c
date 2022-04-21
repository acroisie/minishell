/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:28:18 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/21 17:10:14 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_int_path(t_minishell *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		ft_gc_free(data->path[i]);
	ft_gc_free(data->path);
	ft_gc_free(data->path_temp);
}

void	free_temp(char **temp)
{
	ft_gc_free(temp[1]);
	ft_gc_free(temp[0]);
	ft_gc_free(temp);
}

char	*find_path(t_minishell *data, char *cmd)
{
	int		i;
	char	**temp;

	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
		return (cmd);
	data->path_temp = NULL;
	i = find_in_env(data, "PATH");
	temp = ft_split(data->new_env[i], '=');
	data->path = ft_split(temp[1], ':');
	i = -1;
	while (data->path[++i])
	{
		ft_gc_free(data->path_temp);
		data->path_temp = ft_strjoin(data->path[i], "/");
		data->path_temp = ft_strjoin_free_s1(data->path_temp, cmd);
		if (access(data->path_temp, X_OK) == 0)
		{
			free_temp(temp);
			return (data->path_temp);
		}
	}
	free_int_path(data);
	free_temp(temp);
	return (0);
}
