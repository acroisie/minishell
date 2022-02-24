# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 14:11:10 by lnemor            #+#    #+#              #
#    Updated: 2022/02/24 14:21:23 by acroisie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = gcc 

CC_FLAGS = -Wall -Werror -Wextra

NAME := minishell

SRCS := main.c \
		parse_args.c \
		parse_args_utils.c

OBJS := $(SRCS:.c=.o)

all : libft $(NAME)

$(NAME):		$(addprefix objs/, $(OBJS)) Makefile
					$(CC) -o $(NAME) $(addprefix objs/, $(OBJS)) libft/libft.a -lreadline

objs/%.o:		srcs/%.c includes/minishell.h libft/libft.a
					@mkdir -p objs
					$(CC) $(CC_FLAGS) -c $< -o $@

libft :	
		$(MAKE) -C libft
		
clean :
		rm -rf objs
		make clean -C libft

fclean : clean
		rm -f $(NAME)
		make fclean -C libft

re : fclean all

.PHONY : re clean fclean libft all