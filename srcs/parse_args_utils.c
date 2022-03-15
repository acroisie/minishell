/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:53:16 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/15 17:37:34 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_add_char(char *s1, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1)
		return (ft_strdup(&c));
	if (!c)
		return (s1);
	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = '\0';
	free(s1);
	return (str);
}

void	ft_init_var(t_var *var)
{
	var->lst_cmd = ft_create_cell(NULL);
	var->lst_cmd->args[0] = ft_calloc(1, sizeof(char) * 1);
	dprintf(1, "Here");
	var->lst_cmd->args[0][0] = '\0';
	var->i = 0;
	var->j = 0;
}
