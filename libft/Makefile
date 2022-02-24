# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroisie <acroisie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/03 15:10:13 by acroisie          #+#    #+#              #
#    Updated: 2022/02/08 12:10:46 by acroisie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc -Wall -Wextra -Werror

SRCS = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_free_split.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

BONUS_SRCS = ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

OBJS := $(SRCS:.c=.o)

BONUS_OBJS := $(BONUS_SRCS:.c=*.o)

all : $(NAME)

bonus : $(addprefix objs/, $(BONUS_OBJS))
	ar rcs $(NAME) $(addprefix objs/, $(BONUS_OBJS))

$(NAME) : $(addprefix objs/, $(OBJS))
	ar rcs $(NAME) $(addprefix objs/, $(OBJS))

objs/%.o : %.c libft.h
	mkdir -p objs
	$(CC) -c $< -o $@
	
clean :
	rm -rf objs
	rm -rf $(addprefix objs/, $(OBJS)) $(addprefix objs/, $(BONUS_OBJS))

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all, clean, fclean, bonus