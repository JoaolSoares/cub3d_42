# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 00:10:02 by jlucas-s          #+#    #+#              #
#    Updated: 2023/06/27 20:45:38 by jlucas-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D

FLAGS =			-Werror -Wall -Wextra

CC =			cc

GREEN =			\033[1;32m 
YELLOW =		\033[1;33m 
RED =			\033[1;31m 
NOCOLOR =		\033[0m

INC =			-I ./includes

LIBFTPATH =		./lib
LIBFT =			./lib/libft.a

SRCS =			src/main.c					\
				src/map/init_map.c			\
				src/map/get_infos.c			\
				
OBJS_DIR = 		./objects
OBJS =			${SRCS:%.c=$(OBJS_DIR)/%.o}

all: ${NAME}

${NAME}: ${OBJS}
	@ echo "${YELLOW}-=- Compiling... -=-${NOCOLOR}"
	@ make -s -C ${LIBFTPATH} 
	@ $(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
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

valgrind: ${NAME}
	valgrind --leak-check=full --suppressions=readline.supp --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean run valgrind
