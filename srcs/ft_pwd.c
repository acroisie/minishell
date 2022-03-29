/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:38:39 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/28 11:15:10 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_minishell *data)
{
	dprintf(2, "trst\n");
	getcwd(data->pwd, sizeof(data->pwd));
	ft_putendl_fd(data->pwd, 1);
	exit (0);
	return (0);
}
