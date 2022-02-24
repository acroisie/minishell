/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:50:22 by lnemor            #+#    #+#             */
/*   Updated: 2022/02/24 14:20:34 by acroisie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char			**args;
	struct s_data	*next;

}t_data;

t_data	*ft_lstnew_cell(void);
t_data	*ft_parse_args(char *line);

#endif