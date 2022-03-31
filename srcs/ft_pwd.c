/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:38:39 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/30 19:41:23 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_minishell *data)
{
	getcwd(data->pwd, sizeof(data->pwd));
	ft_putendl_fd(data->pwd, 1);
	exit (0);
	return (0);
}
