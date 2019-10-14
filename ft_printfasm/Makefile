# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 11:47:35 by ahmansou          #+#    #+#              #
#    Updated: 2019/07/12 11:47:09 by ahmansou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = ft_printf
# NAME = ft_printf
# LNAM = libft.a
# LIB = ./libft
# INCL = ./src/ft_printf.h
# SRC = ./src
# W = -Wall -Wextra -Werror

# all: $(NAME)

# $(NAME):
# 		@make -C $(LIB) re
# 			# @gcc $(W) -L $(LIB) -lft $(SRC)/*.c -I $(LIB) -I $(INCL) -o $(NAME)
# 			@gcc -L $(LIB) -lft $(SRC)/*.c -I $(LIB) -I $(INCL) -o $(NAME)

# clean:
# 		@make -C $(LIB) clean

# fclean: clean
# 		@make -C $(LIB) fclean
# 			@/bin/rm -f $(NAME)

# re: fclean all


# ........................

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra

SRC = src/*.c

OBJ = *.o

LIBFT = libft/*.o

all: $(NAME)

$(NAME) :
			make -C libft
			gcc -I ft_printf.h $(FLAGS) -c $(SRC)
			ar rc $(NAME) $(OBJ) $(LIBFT)
			gcc $(NAME)
clean:
			make clean -C libft
			/bin/rm -f $(OBJ)
fclean: clean
			make fclean -C libft
			/bin/rm -f $(OBJ) $(NAME)
re: fclean all