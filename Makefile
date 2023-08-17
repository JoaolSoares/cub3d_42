# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 00:10:02 by jlucas-s          #+#    #+#              #
#    Updated: 2023/08/16 19:43:32 by jlucas-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3d

# FLAGS =			-Werror -Wall -Wextra -lmlx -lXext -lX11 -lm -g -ggdb 

FLAGS =			-lmlx -lXext -lX11 -lm -g -ggdb

CC =			cc

GREEN =			\033[1;32m 
YELLOW =		\033[1;33m 
RED =			\033[1;31m 
NOCOLOR =		\033[0m

INC =			-I ./includes

LIBFTPATH =		./lib
LIBFT =			./lib/libft.a

SRCS =			src/main.c						\
				src/allocs.c					\
				src/read_file.c					\
				src/player.c					\
				src/map/get_map.c				\
				src/map/validation.c			\
				src/textures/textures_mtx.c		\
				src/textures/textures_path.c	\
				src/mlx/init_mlx.c				\
				src/mlx/hooks.c					\
				src/mlx/hooks_utils.c			\
				src/draw/draw.c					\
				src/draw/raycasting.c			\
				src/draw/vertical_line.c		\

OBJS_DIR = 		./objects
OBJS =			${SRCS:%.c=$(OBJS_DIR)/%.o}

all: ${NAME}

${NAME}: ${OBJS}
	@ echo "${YELLOW}-=- Compiling... -=-${NOCOLOR}"
	@ make -s -C ${LIBFTPATH} 
	@ $(CC) $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)
	@ echo "${GREEN}-=- CUB3D MANDATORY SUCCESSFUL COMPILED -=-${NOCOLOR}"

$(OBJS_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(INC) $(FLAGS) -c $< -o $@

clean:
	@ make fclean -s -C ${LIBFTPATH}
	@ rm -rf $(OBJS_DIR)
	@ echo "${RED}-=- CLEANED -=-${NOCOLOR}"

fclean: clean
	@ rm -f $(NAME)

re: fclean all

run: ${NAME}
	@./$(NAME)

.PHONY: all clean fclean run valgrind
