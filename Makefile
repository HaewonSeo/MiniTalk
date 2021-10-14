# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 01:37:10 by haseo             #+#    #+#              #
#    Updated: 2021/10/14 23:02:04 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minitalk
SERVER 			= server
CLIENT			= client
B_SERVER 		= server_bonus
B_CLIENT		= client_bonus

# ----------------------------------
# Compile flag
# ----------------------------------
CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
# CFLAGS			+= -g3 -fsanitize=address
# CFLAGS			+= -g

# ----------------------------------
# Command
# ----------------------------------

CP				= cp
RM				= rm -f
MKDIR			= mkdir -p
RMDIR			= rm -rf
ECHO			= echo

# ----------------------------------
# Echo Color
# ----------------------------------

NOCOLOR			= \033[0m
RED				= \033[0;31m
GREEN			= \033[0;32m
ORANGE			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
LIGHTGRAY		= \033[0;37m
DARKGRAY		= \033[1;30m
LIGHTRED		= \033[1;31m
LIGHTGREEN		= \033[1;32m
YELLOW			= \033[1;33m
LIGHTBLUE		= \033[1;34m
LIGHTPURPLE		= \033[1;35m
LIGHTCYAN		= \033[1;36m
WHITE			= \033[1;37m

# ----------------------------------
# Source & Object file
# ----------------------------------

SERVER_SRC_LIST		=	server.c
CLIENT_SRC_LIST		=	client.c

SERVER_SRC			= $(addprefix $(SRC_DIR)/, $(SERVER_SRC_LIST))
CLIENT_SRC			= $(addprefix $(SRC_DIR)/, $(CLIENT_SRC_LIST))

SERVER_OBJ			= $(addprefix $(OBJ_DIR)/, $(SERVER_SRC_LIST:.c=.o))
CLIENT_OBJ			= $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC_LIST:.c=.o))

B_SERVER_SRC_LIST	=	server_bonus.c
B_CLIENT_SRC_LIST	=	client_bonus.c

B_SERVER_SRC		= $(addprefix $(SRC_DIR)/, $(B_SERVER_SRC_LIST))
B_CLIENT_SRC		= $(addprefix $(SRC_DIR)/, $(B_CLIENT_SRC_LIST))

B_SERVER_OBJ		= $(addprefix $(OBJ_DIR)/, $(B_SERVER_SRC_LIST:.c=.o))
B_CLIENT_OBJ		= $(addprefix $(OBJ_DIR)/, $(B_CLIENT_SRC_LIST:.c=.o))

# ----------------------------------
# Directory
# ----------------------------------

LIBFT_DIR		=	./libft
INC_DIR			=	./inc
SRC_DIR			=	./src
OBJ_DIR			=	./obj
VPATH_DIR		=	./src

vpath %.c $(VPATH_DIR)

# ----------------------------------
# Library
# ----------------------------------

LIBFT			= $(LIBFT_DIR)/libft.a
LIB				= -lft

# ----------------------------------
# Rules
# ----------------------------------

all:			$(OBJ_DIR) $(LIBFT) $(NAME)

bonus:			all $(B_SERVER) $(B_CLIENT)

$(OBJ_DIR):
					@$(MKDIR) $@
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $(OBJ_DIR)$(NOCOLOR)"

$(OBJ_DIR)/%.o: %.c
					@$(CC) -c $(CFLAGS) -I$(INC_DIR) -o $@ $^
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

$(LIBFT):
					@$(MAKE) -C $(LIBFT_DIR)

$(NAME):		$(SERVER) $(CLIENT)

$(SERVER):		$(SERVER_OBJ)
					@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -o $@ $^ $(LIB)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@$(NOCOLOR)"

$(CLIENT):		$(CLIENT_OBJ)
					@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -o $@ $^ $(LIB)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@$(NOCOLOR)"

$(B_SERVER):		$(B_SERVER_OBJ)
					@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -o $@ $^ $(LIB)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@$(NOCOLOR)"

$(B_CLIENT):		$(B_CLIENT_OBJ)
					@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -o $@ $^ $(LIB)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@$(NOCOLOR)"

clean:
					@$(MAKE) -C $(LIBFT_DIR) clean
					@$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)
					@$(RM) $(B_SERVER_OBJ) $(B_CLIENT_OBJ)
					@$(RMDIR) $(OBJ_DIR)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)/$(OBJ_DIR)$(NOCOLOR)"

fclean:			clean
					@$(MAKE) -C $(LIBFT_DIR) fclean
					@$(RM) $(SERVER) $(CLIENT)
					@$(RM) $(B_SERVER) $(B_CLIENT)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)($(SERVER), $(CLIENT))$(NOCOLOR)"

re:				fclean all

#.PHONY: 		all bonus clean fclean re  $(NAME) $(SERVER) $(CLIENT)
