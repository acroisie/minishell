/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:28:18 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/08 12:51:58 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_int_path(t_minishell *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		free(data->path[i]);
	free(data->path);
	free(data->path_temp);
}

void	free_temp(char **temp)
{
	free(temp[1]);
	free(temp[0]);
	free(temp);
}

char	*find_path(t_minishell *data, char *cmd)
{
	int		i;
	char	**temp;

	i = 0;
	data->path_temp = NULL;
	while (ft_strncmp("PATH", data->new_env[i], 4) != 0)
		i++;
	temp = ft_split(data->new_env[i], '=');
	data->path = ft_split(temp[1], ':');
	i = -1;
	while (data->path[++i])
	{
		free(data->path_temp);
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
