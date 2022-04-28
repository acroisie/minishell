/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:38:39 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/28 10:44:58 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_minishell *data)
{
	data->pwd = ft_gc_strdup(getcwd(NULL, 0));
	ft_putendl_fd(data->pwd, 1);
	exit (0);
	return (0);
}
