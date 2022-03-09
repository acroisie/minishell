/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:00:59 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/08 14:55:00 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_minishell *data, char **cmd_args)
{
	int	i;

	i = 0;
	while (ft_strncmp(data->new_env[i], "PWD", 3))
		i++;
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	chdir(cmd_args[1]);
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[i] = ft_strjoin("PWD=", data->cd_pwd);
}
