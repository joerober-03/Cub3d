# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 10:52:31 by dferreir          #+#    #+#              #
#    Updated: 2023/08/23 11:44:29 by dferreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREEN		= \033[0;32m
RED 		= \033[0;31m
BOLD		= \033[1m
NORMAL		= \033[0m
UP 			= \033[A
CUT 		= \033[K

#OUTPUT
NAME		= cub3D

#FILES
LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/
LIBFT_HEADS	= $(LIBFT_DIR)incs/

MINILIBX	= $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = ./libmlx/

HEADS_LIST	= cub3d.h
HEADS_DIR	= ./incs/
HEADS		= $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIR	= ./srcs/
BONUS_SRCS_DIR	= ./srcs_bonus/
SRCS_FILES	= main.c graphics.c hooks.c utils.c parsing.c mini_map.c raycaster_utils.c colors.c map.c map_buffer.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_FILES}}
BONUS_SRCS	:= ${addprefix ${BONUS_SRCS_DIR}, ${SRCS_FILES}}

OBJS_DIR	= ./objs/
BONUS_OBJS_DIR	= ./objs_bonus/
OBJS_FILES	:= ${SRCS_FILES:.c=.o}
BONUS_OBJS_FILES	:= ${SRCS_FILES:.c=.o}
OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS_FILES}}
BONUS_OBJS	:= ${addprefix ${BONUS_OBJS_DIR}, ${BONUS_OBJS_FILES}}

#COMMANDS
CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
MKDIR		= mkdir -p
RM			= rm -rf
LIBS		= -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework AppKit
INCS		= -I$(HEADS_DIR) -I$(LIBFT_HEADS) -I$(MINILIBX_DIR)

all: ${NAME}

#Compile normal executable
${NAME}: ${LIBFT} ${MINILIBX} ${OBJS_DIR} ${OBJS}
	@${CC} ${CFLAGS} ${LIBS} ${INCS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

#Create objects directory
${OBJS_DIR}:
	@${MKDIR} ${OBJS_DIR}

${BONUS_OBJS_DIR}:
	@${MKDIR} ${BONUS_OBJS_DIR}

#Compile normals objects
${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@echo "$(RED)[$(BOLD)Compiling$(NORMAL)$(RED)]$(NORMAL) $<$(UP)$(CUT)"
	@${CC} -g ${CFLAGS} ${INCS} -o $@ -c $<

${BONUS_OBJS_DIR}%.o: ${BONUS_SRCS_DIR}%.c
	@echo "$(RED)[$(BOLD)Compiling$(NORMAL)$(RED)]$(NORMAL) $<$(UP)$(CUT)"
	@${CC} -g ${CFLAGS} ${INCS} -o $@ -c $<

${LIBFT}:
	@make -C ${LIBFT_DIR}

${MINILIBX}:
	@make -C ${MINILIBX_DIR}

#Clean obj files
clean:
	@make -C ${LIBFT_DIR} clean
	@make -C ${MINILIBX_DIR} clean
	@${RM} ${OBJS_DIR}
	@${RM} ${BONUS_OBJS_DIR}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) object files deleted"

#Clean objs files and name
fclean:	clean
	@${RM} ${MINILIBX}
	@${RM} ${LIBFT}
	@${RM} ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) deleted"

bonus: ${LIBFT} ${MINILIBX} ${BONUS_OBJS_DIR} ${BONUS_OBJS}
	@${CC} ${CFLAGS} ${LIBS} ${INCS} ${BONUS_OBJS} -o ${NAME}
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) created and compiled object files"
	@echo "$(GREEN)[$(BOLD)OK$(NORMAL)$(GREEN)]$(NORMAL) $(BOLD)$(NAME)$(NORMAL) is ready"

#valgrind: all
#	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re #valgrind

