/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/07 13:36:04 by lnemor           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_dest(t_minishell *data, char **dest)
{
	int	i;

	i = -1;
	while (dest[++i])
			data->new_env[i] = ft_strdup(dest[i]);
		data->new_env[i] = NULL;
}

int	check_arg(char **args)
{
	int	equal;
	int	j;

	equal = 0;
	j = 0;
	while (args[1][j])
	{
		if (!ft_isalpha(args[1][0]))
			return (return_error_export("export: `", args[1],
					"': not a valid identifier", 1));
		if (args[1][j] == '=')
		{
			equal++;
			j++;
		}
		if (ft_isalpha(args[1][j]) || args[1][j] == '_')
			j++;
		else
			return (return_error_export("export: `", args[1],
					"': not a valid identifier", 1));
	}
	return (equal);
}

char	**replace_exist_line(t_minishell *data, char **args, char **dest)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(args[1], '=');
	while (data->new_env[++i] != NULL)
	{
		if (!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0])))
			break ;
	}
	if (i == ft_destlen(data->new_env) && ft_strncmp(data->new_env[i],
			split[0], ft_strlen(split[0])))
		data->new_env[i] = ft_strdup(args[1]);
	else
		return (ft_addline(dest, args[1]));
	ft_free_split(split);
	return (dest);
}

void	ft_export(t_minishell *data, char **args)
{
	char	**dest;
	int		i;

	i = -1;
	dest = malloc(sizeof(char *) * ft_destlen(data->new_env) + 2);
	while (data->new_env[++i])
		dest[i] = ft_strdup(data->new_env[i]);
	dest[i] = NULL;
	if (!args[1])
		return (display_export(dest));
	else
	{
		if (check_arg(args) > 0)
			dest = replace_exist_line(data, args, dest);
		else
		{
			if (check_arg(args) == 0)
				args[1] = ft_add_char(args[1], '=');
			dest = ft_addline(dest, args[1]);
			copy_dest(data, dest);
		}
		ft_free_split(dest);
		return ;
	}
}
