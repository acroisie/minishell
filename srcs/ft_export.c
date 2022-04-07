/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/07 18:24:26 by lnemor           ###   ########lyon.fr   */
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
	int		equal;
	int		j;
	char	*temp;

	equal = 0;
	j = 0;
	temp = ft_strdup(args[1]);
	while (temp[j])
	{
		if (!ft_isalpha(temp[0]) && !(temp[0] == '_'))
			return (return_error_export("export: `", temp,
					"': not a valid identifier", 1));
		if (temp[j] == '=')
		{
			equal++;
		}
		if (ft_isalnum(temp[j]) || temp[j] == '_' || temp[j] == '=')
			j++;
		else
			return (return_error_export("export: `", temp,
					"': not a valid identifier", 1));
	}
	free(temp);
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
	if (i != ft_destlen(data->new_env) && !ft_strncmp(data->new_env[i],
			split[0], ft_strlen(split[0])))
	{
		dest[i] = ft_strdup(args[1]);
	}
	else
		return (ft_addline(dest, args[1]));
	ft_free_split(split);
	return (dest);
}

void	ft_export(t_minishell *data, t_lst_cmd *lst_cmd)
{
	char	**dest;
	int		i;

	i = -1;
	dest = ft_calloc(sizeof(char *), ft_destlen(data->new_env) + 2);
	while (data->new_env[++i])
		dest[i] = ft_strdup(data->new_env[i]);
	dest[i] = NULL;
	if (!lst_cmd->args[1])
		return (display_export(dest));
	else
	{
		if (check_arg(lst_cmd->args) > 0)
		{
			dest = replace_exist_line(data, lst_cmd->args, dest);
			copy_dest(data, dest);
		}
		ft_free_split(dest);
		return ;
	}
}
