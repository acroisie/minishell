# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 14:11:10 by lnemor            #+#    #+#              #
#    Updated: 2022/03/15 17:32:38 by acroisie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = gcc 

CC_FLAGS = -Wall -Wextra -Werror -g

NAME := minishell

SRCS := cells_utils.c \
		exec.c \
		find_path.c \
		ft_builtins.c \
		ft_cd.c \
		ft_env.c \
		main.c \
		parse_args_process.c \
		parse_args_utils.c \
		parse_args.c

OBJS := $(SRCS:.c=.o)

all : libft $(NAME)

$(NAME):		$(addprefix objs/, $(OBJS)) Makefile
					$(CC) -o $(NAME) $(addprefix objs/, $(OBJS)) libft/libft.a -lreadline 

objs/%.o:		srcs/%.c includes/minishell.h libft/libft.a
					@mkdir -p objs
					$(CC) $(CC_FLAGS) -c $< -o $@

libft :	
		$(MAKE) -C libft
		$(MAKE) bonus -C libft
		
clean :
		rm -rf objs
		make clean -C libft

fclean : clean
		rm -f $(NAME)
		make fclean -C libft

re : fclean all

.PHONY : re clean fclean libft all