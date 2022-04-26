/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnemor <lnemor@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/26 16:37:14 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_dest(t_minishell *data, char **dest)
{
	int	i;

	i = -1;
	while (dest[++i])
		data->new_env[i] = ft_gc_strdup(dest[i]);
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

void	replace_exist_line(t_minishell *data, char *args)
{
	char	**split;
	int		i;
	char	*temp;

	i = -1;
	temp = ft_gc_strdup(args);
	split = ft_split(temp, '=');
	while (data->new_env[++i] != NULL)
	{
		if ((!ft_strncmp(data->new_env[i], split[0], ft_strlen(split[0]))))
			break ;
	}
	if (i != ft_destlen(data->new_env) && !ft_strncmp(data->new_env[i],
			split[0], ft_strlen(split[0])))
		data->new_env[i] = ft_gc_strdup(temp);
	else
		data->new_env = ft_addline(data->new_env, temp);
	ft_free_split(split);
}

void	ft_export(t_minishell *data, t_lst_cmd *lst_cmd)
{
	int		i;
	int		check;

	if (lst_cmd->args[1])
	{
		i = 0;
		check = 0;
		while (lst_cmd->args[++i] != NULL)
		{
			check = check_arg(lst_cmd->args[i]);
			if (check == 0 && count_equal(lst_cmd->args[i]) > 0)
				replace_exist_line(data, lst_cmd->args[i]);
			else if (check == 0 && count_equal(lst_cmd->args[i]) == 0
				&& !is_in_env(data, lst_cmd->args[i]))
				data->new_env = ft_addline(data->new_env, lst_cmd->args[i]);
		}
	}
	else
		display_export(data);
}
