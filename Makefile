# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 19:09:47 by dmusulas          #+#    #+#              #
#    Updated: 2024/05/14 21:46:52 by dmusulas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC           = cc
CFLAGS       = -Wall -Wextra -Werror -g -Iinclude -Isrc
NAME         = pipex
MAKE_LIB     = make -C
RM			 = rm -rf

# Libraries
LIBFT_DIR    = libft
LIBFT_FILENAME = libft.a
LIBFT        = $(LIBFT_DIR)/$(LIBFT_FILENAME)
CFLAGS		+= -I$(LIBFT_DIR)/include

# Sources
VPATH        = src:include
INCLUDES     = pipex.h
PIPEX_SRCS   = main.c \
			   errors.c \
			   files.c \
			   parse_args.c \
			   pipex.c \
			   utils.c
PIPEX_OBJS = $(PIPEX_SRCS:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(PIPEX_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(PIPEX_OBJS) $(LIBFT) -o $@


$(PIPEX_OBJS): obj/%.o : src/%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)


clean:
	make clean -C $(LIBFT_DIR)
	rm -rf obj

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: clean fclean all re
