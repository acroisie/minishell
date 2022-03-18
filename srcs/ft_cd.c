/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:00:59 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/18 15:56:19 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_minishell *data, char **cmd_args)
{
	int		i;
	int		j;
	int		k;
	char	**home;

	i = 0;
	j = 0;
	k = 0;
	while (ft_strncmp(data->new_env[i], "PWD", 3))
		i++;
	while (ft_strncmp(data->new_env[k], "OLDPWD", 6))
		k++;
	while (ft_strncmp(data->new_env[j], "HOME", 4))
		j++;
	home = ft_split(data->new_env[j], '=');
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[k] = ft_strjoin("OLDPWD=", data->cd_pwd);
	if (cmd_args[1])
	{
		if (chdir(cmd_args[1]))
			dprintf(2, "error file\n");
	}
	else if (!cmd_args[1])
	{
		if (chdir(home[1]))
			dprintf(2, "no home\n");
	}
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[i] = ft_strjoin("PWD=", data->cd_pwd);
}
