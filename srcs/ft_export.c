/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:54:31 by lnemor            #+#    #+#             */
/*   Updated: 2022/04/01 10:06:44 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//ce fdp de export segfault
void	ft_export(t_minishell *data, char **args)
{
	char	**dest;
	char	*temp;
	int		i;
	int		j;
	int		equal;
	// char	**split;

	i = -1;
	dest = malloc(sizeof(char *) * ft_destlen(data->new_env) + 1);
	while (data->new_env[++i])
		dest[i] = ft_strdup(data->new_env[i]);
	i = -1;
	while (dest[++i] && dest[i + 1])
	{
		if (ft_strcmp(dest[i], dest[i + 1]) > 0)
		{
			temp = dest[i];
			dest[i] = dest[i + 1];
			dest[i + 1] = temp;
			i = -1;
		}
	}
	if (!args[1])
	{
		i = -1;
		while (dest[++i])
		{
			dest[i] = ft_strjoin_free_s2("declare -x ", dest[i]);
			ft_putendl_fd(dest[i], 1);
			free(dest[i]);
		}
		free (dest);
		return ;
	}
	else
	{
		equal = 0;
		j = 0;
		i = -1;
		while (args[1][j])
		{
			if (!ft_isalpha(args[1][0]))
				return (return_error_export("export: `", args[1],
						"': not a valid identifier", 1));
			if (args[1][j] == '=')
				equal++;
			if (ft_isalpha(args[1][j]) || args[1][j] == '_')
				j++;
		}
		if (equal == 0)
			args[1] = ft_add_char(args[1], '=');
		else if (equal > 0)
		{
			// split = ft_split(args[1], '=');
			
		}
		dest = ft_addline(dest, args[1]);
		dest[(ft_destlen(dest))] = NULL;
		while (dest[++i])
		{
			data->new_env[i] = ft_strdup(dest[i]);
			dprintf(2, "da");
			free(dest[i]);
		}
		free(dest);
	}
}
