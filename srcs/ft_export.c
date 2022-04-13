/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/13 13:25:18 by lnemor           ###   ########lyon.fr   */
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
	ft_free_split(dest);
}

int	count_equal(char *args)
{
	int	j;
	int	equal;

	equal = 0;
	j = -1;
	while (args[++j])
	{
		if (!ft_isalpha(args[0]) && !(args[0] == '_'))
			return (return_error_export("export: `", args,
					"': not a valid identifier", 1));
		if (args[j] == '=')
			equal++;
	}
	return (equal);
}

int	check_arg(char *args)
{
	int		j;
	char	**temp;

	temp = ft_split(args, '=');
	j = 0;
	while (temp[0][j])
	{
		if (!ft_isalpha(temp[0][0]) && !(temp[0][0] == '_'))
			return (return_error_export("export: `", temp[0],
					"': not a valid identifier", 1));
		if (ft_isalnum(temp[0][j]) || temp[0][j] == '_' || temp[0][j] == '='
			|| ft_isspace(j))
			j++;
		else
			return (return_error_export("export: `", temp[0],
					"': not a valid identifier", 1));
	}
	ft_free_split(temp);
	return (0);
}

char	**replace_exist_line(t_minishell *data, char **args, char **dest)
{
	char	**split;
	int		i;
	char	*temp;
	int		j;

	j = 1;
	while (args[j])
	{
		i = -1;
		dprintf(2, "{%s}\n", args[j]);
		temp = ft_strdup(args[j]);
		split = ft_split(temp, '=');
		while (data->new_env[++i] != NULL)
		{
			if (!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0])))
				break ;
		}
		if (i != ft_destlen(data->new_env) && !ft_strncmp(data->new_env[i],
				split[0], ft_strlen(split[0])))
			dest[i] = ft_strdup(temp);
		else
			dest = ft_addline(dest, temp);
		ft_free_split(split);
		dprintf(2, "{%s}\n", args[j]);
		j++;
	}
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
		i = 0;
		while (lst_cmd->args[i])
		{
			if (check_arg(lst_cmd->args[i]) == 0
				&& count_equal(lst_cmd->args[i]) > 0)
			{
				dest = replace_exist_line(data, lst_cmd->args, dest);
				return (copy_dest(data, dest));
			}
			i++;
		}
		ft_free_split(dest);
		return ;
	}
}
