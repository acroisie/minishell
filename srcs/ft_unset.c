/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:28:13 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/13 13:01:40 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_arg_unset(char *args)
{
	int		j;

	j = 0;
	while (args[j])
	{
		if (!ft_isalpha(args[0]) && !(args[0] == '_'))
			return (return_error_export("export: `", args,
					"': not a valid identifier", 1));
		if (ft_isalnum(args[j]) || args[j] == '_' || ft_isspace(j))
			j++;
		else
			return (return_error_export("export: `", args,
					"': not a valid identifier", 1));
	}
	return (0);
}

int	ft_unset(t_minishell *data, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (check_arg_unset(args[i]))
			return (0);
		i++;
	}
	i = 0;
	while (data->new_env[i])
	{
		if (ft_strncmp(args[1], data->new_env[i], ft_strlen(args[1])) == 0)
			break ;
		i++;
	}
	if (i == ft_destlen(data->new_env))
		return (1);
	if (data->new_env[i])
		data->new_env[i] = ft_strdup("");
	return (0);
}
