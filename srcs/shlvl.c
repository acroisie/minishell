/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:31:22 by lnemor            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/25 12:36:37 by lnemor           ###   ########lyon.fr   */
=======
/*   Updated: 2022/04/24 11:19:22 by lnemor           ###   ########lyon.fr   */
>>>>>>> 76b9c2039c73ada6a9ce13c80ae6438bc57bc059
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
