# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 16:43:27 by jekim             #+#    #+#              #
#    Updated: 2021/12/07 02:35:58 by jiychoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc
CCFLAG		=	-Wall -Wextra -Werror
LIBFLAG		=	-L$(LIBFT_DIR) -lft -lreadline
G			=	-g3
INCLUDE		=	-I$(INC_DIR) -I$(LIBFT_DIR)

OBJ_DIR		=	./obj/
SRC_DIR		=	./src/
UTILS_DIR	= 	./src/utils/
PARSER_DIR	=	./src/parser/
CMD_DIR		=	./src/cmd/
EXEC_DIR	=	./src/executor/
INC_DIR		=	./includes/
LIBFT_DIR	=	./libft/

SRC_FILE		=	minishell.c \
					environ.c

PARSER_FILE 	=	parser.c \
					parser_isbs.c \
					parser_split.c	\
					parser_lst.c \
					parser_quotetrim.c \
					parser_guard_syntax.c \
					parser_del_nullish_token.c \
					parser_replace_env.c \
					parser_type.c \
					parser_util.c

UTILS_FILE		=	utils.c \
					ft_strncpy.c \
					ft_strndup.c \
					env_name_check.c \
					find_env.c \
					save_env.c \
					add_shlvl.c \
					builtin_error.c \
					check_flag.c \
					check_argument.c \
					free_token.c \
					ft_free_char2d.c \
					get_redir_fd.c \
					if_builtin.c \

CMD_FILE		=	cd.c \
					echo.c \
					env.c \
					exit.c \
					export.c \
					pipe_utils.c \
					pipe.c \
					pwd.c \
					unset.c

EXEC_FILE		=	executor_utils1.c \
					executor_utils2.c \
					executor.c

MAIN_OBJ_FILE	=	$(SRC_FILE:.c=.o)
PARSER_OBJ_FILE	=	$(PARSER_FILE:.c=.o)
UTILS_OBJ_FILE	=	$(UTILS_FILE:.c=.o)
CMD_OBJ_FILE	=	$(CMD_FILE:.c=.o)
EXEC_OBJ_FILE	=	$(EXEC_FILE:.c=.o)

MAIN_OBJ		=	$(addprefix $(OBJ_DIR), $(MAIN_OBJ_FILE))
PARSER_OBJ		=	$(addprefix $(OBJ_DIR), $(PARSER_OBJ_FILE))
UTILS_OBJ		=	$(addprefix $(OBJ_DIR), $(UTILS_OBJ_FILE))
CMD_OBJ			=	$(addprefix $(OBJ_DIR), $(CMD_OBJ_FILE))
EXEC_OBJ		=	$(addprefix $(OBJ_DIR), $(EXEC_OBJ_FILE))

OBJ				= 	$(MAIN_OBJ)	\
					$(PARSER_OBJ)	\
					$(UTILS_OBJ)	\
					$(CMD_OBJ)	\
					$(EXEC_OBJ)

all			:	$(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(UTILS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(CMD_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(OBJ_DIR)%.o : $(EXEC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(G) $(CCFLAG) $(INCLUDE) $< -c -o $@

$(NAME)		:	$(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(G) $(CCFLAG) $(OBJ) $(LIBFLAG) $(INCLUDE) -o $@
	@echo "\033[0;92m* $(NAME) program file was created *\033[0m"

debug		:	$(NAME)
	@$(MAKE) re
	lldb $(NAME)

clean		:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C ./libft clean
	@echo "\033[0;91m* $(NAME)'s object files were removed* \033[0m"

fclean		:	clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "\033[0;91m* $(NAME) were removed* \033[0m"

re			:	fclean all

.PHONY: all, clean, fclean, re
