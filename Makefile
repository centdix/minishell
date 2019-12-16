# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/07 23:13:40 by lmartin           #+#    #+#              #
#    Updated: 2019/12/16 03:51:24 by lmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END		=	\x1b[0m
_BOLD		=	\x1b[1m
_UNDER		=	\x1b[4m
_REV		=	\x1b[7m

# Colors
_GREY		=	\x1b[30m
_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_BLUE		=	\x1b[34m
_PURPLE		=	\x1b[35m
_CYAN		=	\x1b[36m
_WHITE		=	\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\x1b[40m
_IRED		=	\x1b[41m
_IGREEN		=	\x1b[42m
_IYELLOW	=	\x1b[43m
_IBLUE		=	\x1b[44m
_IPURPLE	=	\x1b[45m
_ICYAN		=	\x1b[46m
_IWHITE		=	\x1b[47m

# **************************************************************************** #

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror


# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_HEADERS =	./includes/

DIR_SRCS	=	./srcs/

DIR_OBJS	=	./compiled_srcs/

DIR_COMMANDS=	commands/

DIR_CMDS_RUN=	commands/run/

DIR_ENV_V	=	env_variables/

DIR_ERRORS	=	errors/

DIR_PARSING =	parsing/

DIR_STYLE	=	style/

DIR_UTILS	=	utils/


# FILES #

SRC			=	commands/run/run_bin.c \
				commands/run/run_cd.c \
				commands/run/run_echo.c \
				commands/run/run_env.c \
				commands/run/run_exit.c \
				commands/run/run_export.c \
				commands/run/run_pwd.c \
				commands/run/run_unset.c \
				commands/commands.c \
				commands/lstcommands.c \
				\
				env_variables/env_v_utils.c \
				env_variables/lstenv_v.c \
				\
				errors/command_errors.c \
				\
				parsing/get_data_no_space.c \
				parsing/get_data_one_space.c \
				parsing/get_data.c \
				parsing/parsing_bin.c \
				parsing/parsing_cd.c \
				parsing/parsing_echo.c \
				parsing/parsing_env.c \
				parsing/parsing_exit.c \
				parsing/parsing_export.c \
				parsing/parsing_pipe.c \
				parsing/parsing_pwd.c \
				parsing/parsing_redirect_double_output.c \
				parsing/parsing_redirect_input.c \
				parsing/parsing_redirect_simple_output.c \
				parsing/parsing_unset.c \
				parsing/parsing_utils.c \
				parsing/parsing.c \
				\
				style/style.c \
				\
				utils/ft_free_return.c \
				utils/ft_isalpha.c \
				utils/ft_isdigit.c \
				utils/ft_isquote.c \
				utils/ft_isseparator.c \
				utils/ft_isspace.c \
				utils/ft_itoa.c \
				utils/ft_multifree.c \
				utils/ft_setint_and_return.c \
				utils/ft_strchr.c \
				utils/ft_strcmp.c \
				utils/ft_strdup.c \
				utils/ft_strjoin.c \
				utils/ft_strlen.c \
				utils/ft_strncmp.c \
				\
				minishell.c

SRCS		=	$(SRC)


# COMPILED_SOURCES #

OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

NAME 		=	minishell


# **************************************************************************** #

## RULES ##

# VARIABLES RULES #

$(NAME):		$(OBJS)
				@echo "$(_GREEN) All files compiled into '$(DIR_OBJS)'. $(_END)✅"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@echo "$(_GREEN) Executable '$(NAME)' created. $(_END)✅"

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJS):
				@mkdir $(DIR_OBJS)
				@mkdir $(DIR_OBJS)$(DIR_COMMANDS)
				@mkdir $(DIR_OBJS)$(DIR_CMDS_RUN)
				@mkdir $(DIR_OBJS)$(DIR_ENV_V)
				@mkdir $(DIR_OBJS)$(DIR_ERRORS)
				@mkdir $(DIR_OBJS)$(DIR_PARSING)
				@mkdir $(DIR_OBJS)$(DIR_STYLE)
				@mkdir $(DIR_OBJS)$(DIR_UTILS)


# OBLIGATORY PART #

all:			$(NAME)

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED)'"$(DIR_OBJS)"' has been deleted. $(_END)🗑️"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(_RED)'"$(NAME)"' has been deleted. $(_END)🗑️"

re:				fclean all

# NORME #

norm:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

# BONUS #

bonus:			all

re_bonus:		fclean bonus

# PHONY #

.PHONY:			all, clean, fclean, re, bonus, re_bonus
