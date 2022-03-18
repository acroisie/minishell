/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:16:53 by lnemor            #+#    #+#             */
/*   Updated: 2022/03/18 15:21:14 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_lst_cmd *lst_cmd)
{
	if (lst_cmd->args[0] == NULL)
		return (0);
	if (ft_strncmp(lst_cmd->args[0], "cd", ft_strlen("cd")) == 0
		|| ft_strncmp(lst_cmd->args[0], "env",
			ft_strlen("env")) == 0)
		return (1);
	else
		return (0);
}

void	do_builtin(t_minishell *data, t_lst_cmd *lst_cmd)
{
	if (ft_strncmp(lst_cmd->args[0], "cd", ft_strlen(lst_cmd->args[0])) == 0)
		ft_cd(data, lst_cmd->args);
	if (ft_strncmp(lst_cmd->args[0], "env", ft_strlen(lst_cmd->args[0])) == 0)
		ft_env(data);
}
