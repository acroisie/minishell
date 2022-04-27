/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:31:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/27 14:28:38 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**replace_exist_line_2(t_minishell *data, char *args, char **dest)
{
	char	**split;
	char	*temp;
	int		shlvl;

	if (args)
	{
		temp = ft_gc_strdup(args);
		split = ft_split(temp, '=');
		shlvl = ft_atoi(split[1]) + 1;
		temp = ft_strjoin("SHLVL=", ft_itoa(shlvl));
		ft_free_split(split);
	}
	else
		temp = ft_gc_strdup("SHLVL=1");
	if (is_in_env(data, "SHLVL"))
		dest[find_in_env(data, "SHLVL")] = ft_gc_strdup(temp);
	else
	{
		getcwd(data->pwd, sizeof(data->pwd));
		dest = ft_addline(dest, ft_strjoin("PWD=", data->pwd));
		dest = ft_addline(dest, temp);
	}
	return (dest);
}

void	oldpwd(t_minishell *data)
{
	if (is_in_env(data, "OLDPWD"))
		data->new_env[find_in_env(data, "OLDPWD")] = ft_gc_strdup(data->cd_pwd);
	else
	{
		getcwd(data->pwd, sizeof(data->pwd));
		data->new_env = ft_addline(data->new_env,
				ft_strjoin("OLDPWD=", data->cd_pwd));
	}
}
