/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:00:59 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/23 20:30:42 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd2(t_minishell *data, int i, int j, char **cmd_args)
{
	char	**home;

	home = ft_split(data->new_env[j], '=');
	if (cmd_args[1])
	{
		if (chdir(cmd_args[1]) == -1)
		{
			return_error_builtin("cd: ", cmd_args[1],
				": No such file or directory", 1);
			dprintf(2, "test\n");
			g_rvalue = 1;
			exit(1);
		}
	}
	else if (!cmd_args[1])
		chdir(home[1]);
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[i] = ft_strjoin("PWD=", data->cd_pwd);
}

void	ft_cd(t_minishell *data, char **cmd_args)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	while (data->new_env[++i])
		if (ft_strncmp(data->new_env[i], "PWD", 3) == 0)
			break ;
	while (data->new_env[++k])
		if (ft_strncmp(data->new_env[k], "OLDPWD", 6) == 0)
			break ;
	while (data->new_env[++j])
		if (ft_strncmp(data->new_env[j], "HOME", 4) == 0)
			break ;
	if (j == ft_destlen(data->new_env) && !cmd_args[1])
	{
		return_error_builtin("cd: ", "HOME", " not set", 1);
		g_rvalue = 1;
		exit(1);
	}
	getcwd(data->cd_pwd, sizeof(data->cd_pwd));
	data->new_env[k] = ft_strjoin("OLDPWD=", data->cd_pwd);
	ft_cd2(data, i, j, cmd_args);
}
