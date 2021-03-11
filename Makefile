# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 22:44:15 by ngonzo            #+#    #+#              #
#    Updated: 2021/01/19 19:21:26 by fignigno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
FLAGS = -Wall -Werror -Wextra -g -Imlx
SRCS = 	src/main.c src/clean.c src/description.c src/get_res.c src/key_hook.c\
		src/print_errors.c src/print_figures.c src/ray_cast.c\
		src/reader.c src/save_bmp.c src/sort_sprites.c src/sprite.c src/textures.c\
		src/valid.c gnl/get_next_line.c gnl/get_next_line_utils.c src/right_order.c\
		src/check_info.c src/map_game.c
OBJS = $(SRCS:c=o)
LIBFT = ./libft/libft.a
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit libmlx.dylib

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	$(MAKE) -C ./mlx
	mv ./mlx/libmlx.dylib ./

$(OBJS): %.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./mlx

fclean: clean
	rm -rf $(NAME)
	rm -rf screenshot.bmp
	rm -rf libmlx.dylib
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all, clean, fclean, re
