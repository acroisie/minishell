/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:38:39 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/23 20:48:52 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_minishell *data)
{
	int	i;

	i = -1;
	while (data->new_env[++i])
		if (ft_strncmp(data->new_env[i], "PWD", 3) == 0)
			break ;
	ft_putendl_fd(data->new_env[i], 1);
	return (0);
}
