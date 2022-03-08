/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:47:25 by acroisie          #+#    #+#             */
/*   Updated: 2022/03/08 10:16:31 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	detect_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static	int	args_count(const char *str, char sep)
{
	int	i;
	int	count;
	int	str_len;

	i = 1;
	count = 0;
	str_len = ft_strlen(str);
	while (i <= str_len)
	{
		if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\0')
					exit (1); //Add a clean exit with message: "Unclosed quotes"
			}
		}
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
			{
				if (str[i] == '\0')
					exit (1); //Add a clean exit with message: "Unclosed quotes"
			}
		}
		if (!detect_sep(str[i - 1], sep) && (detect_sep(str[i], sep)
				|| str[i] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**fill_tab(const char *str, char **tab, char sep)
{
	int		start;
	int		end;
	int		i;
	int		j;

	start = 0;
	i = 0;
	while (i < args_count(str, sep))
	{
		j = 0;
		while (detect_sep(str[start], sep))
			start++;
		end = start;
		while (!detect_sep(str[end], sep) && str[end] != '\0')
		{
			if (str[end] == '"')
			{
				while (str[end] && str[++end] != '"')
					;
			}
			if (str[end] == '\'')
			{
				while (str[end] && str[++end] != '\'')
					;
			}
			end++;
		}
		tab[i] = malloc((end - start + 1) * sizeof(char));
		if (tab[i] == NULL)
			return (0);
		while (start < end)
			tab[i][j++] = str[start++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split_args(char const *s, char c)
{
	char	**tab;
	int		word_nb;

	// dprintf(1, "here\n"); // To delete
	if (!s)
		return (NULL);
	word_nb = args_count(s, c);
	tab = malloc((word_nb + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(s, tab, c);

	return (tab);
}

t_lst_cmd	*ft_parse_args(char *line)
{
	t_lst_cmd	*lst_cmd;
	char		**temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = ft_split_args(line, '|');
	// dprintf(1, "temp = %s\n", temp[0]); // To delete
	lst_cmd = ft_create_cell(ft_split_args(temp[0], ' '), NULL);
	// dprintf(1, "temp2 = %s\n", lst_cmd->args[1]); // To delete“
	while (temp[i])
		i++;
	if (i > 1)
	{
		lst_cmd->args = ft_split_args(temp[j], ' ');
		j++;
		while (j < i)
		{
			ft_lstadd_cell(lst_cmd, ft_split_args(temp[j], ' '));
			j++;
		}
	}
	return (lst_cmd);
}
