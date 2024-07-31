# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 11:14:10 by aschenk           #+#    #+#              #
#    Updated: 2024/05/29 11:29:52 by aschenk          ###   ########.fr        #
#
#                                                                              #
# **************************************************************************** #

#################
## DEFINITIONS ##
#################

NAME :=			minishell

# SOURCE FILES
SRCS_DIR :=		src
SRCS_FILES :=	main.c \
				free.c \
				utils.c \
				0_check_input/check_quotation.c \
				1_tokenizer/tokenizer_get_tokens.c \
				1_tokenizer/tokenizer_redirection.c \
				1_tokenizer/tokenizer_pipe.c \
				1_tokenizer/tokenizer_utils.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/pwd.c \
				builtins/unset.c \
				errors/cd_errors.c \
				errors/env_errors.c \
				errors/exit_errors.c \
				errors/export_errors.c \
				errors/pwd_errors.c \
				errors/unset_errors.c \
				parsing/parsing.c \
				standard_functions/count.c \
				standard_functions/free_functions.c \
				standard_functions/modified_standards.c \
				struct_inits/init_cd.c \
				struct_inits/init_data.c \
				struct_inits/init_env.c \
				struct_inits/init_export.c \

SRCS :=			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

# OBJECT FILES
OBJS_DIR :=		obj
OBJS :=			$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# HEADER FILES
HDRS_DIR :=		include
HDRS_FILES := 	minishell.h \
				config.h \
				tokenizer.h \
				errors.h

HDRS :=			$(addprefix $(HDRS_DIR)/, $(HDRS_FILES))

# LIBFT
LIBFT_DIR :=	libft
LIBFT_LIST :=	libft.h \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strncmp.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_memset.c \
				ft_memchr.c \
				ft_memcpy.c \
				ft_memcmp.c \
				ft_memmove.c \
				ft_bzero.c \
				ft_atoi.c \
				ft_strdup.c \
				ft_calloc.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_strcmp.c \
				ft_isbinary.c \
				get_next_line_bonus.c \
				ft_printf_utils.c \
				ft_printf.c \
				ft_atoi_base.c

LIBFT_FILES := $(addprefix $(LIBFT_DIR)/, $(LIBFT_LIST))
LIBFT :=		$(LIBFT_DIR)/libft.a

# LINKING LIBS
LIB_FLAGS  :=	-L$(LIBFT_DIR) -lft -lreadline -lhistory

# COMPILER
CC :=			cc
CFLAGS := 		-I$(HDRS_DIR) -I$(LIBFT_DIR)
CFLAGS :=		-Werror -Wextra -Wall -I$(HDRS_DIR) -I$(LIBFT_DIR)
CFLAGS +=		-Wpedantic -g
#CFLAGS +=		-fsanitize=address

# Used for progress bar
TOTAL_SRCS :=	$(words $(SRCS))
SRC_NUM :=		0

# ANSI escape codes for colors and styles
RESET =			\033[0m
BOLD =			\033[1m
RED =			\033[31;2m
GREEN =			\033[32m
YELLOW =		\033[33m
L_RED :=		\033[91m

###########
## RULES ##
###########

# Default target
all:		$(LIBFT) $(NAME)

# Build libft library by calling 'make' in LIBFT_DIR.
# This target will be executed if libft.a is missing or
# if any of the listed .c or .h files in LIBFT_DIR are modified.
$(LIBFT):	$(LIBFT_FILES)
	@make -s -C $(LIBFT_DIR)
	@echo ""

# Target $(NAME) depends on object files $(OBJS) and the libft library.
$(NAME):	$(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(YELLOW)\n$(NAME) successfully compiled.$(RESET)"
	@echo "\nUsage: './minishell' to start the program, then use it like bash.\n"

# COMPILATION PROGRESS BAR
# Rule to define how to generate object files (%.o) from corresponding
# source files (%.c). Each .o file depends on the associated .c file and the
# project header files.
# Last line:
# -c:		Generates o. files without linking.
# -$<:		Represents the first prerequisite (the c. file).
# -o $@:	Output file name;  '$@' is replaced with target name (the o. file).
$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HDRS)
	@mkdir -p $(@D)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d/%d - " $(SRC_NUM) $(TOTAL_SRCS)
	@printf "%d%% $(RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -D FD_SIZE=$(FD_SIZE) -c $< -o $@

# Rule to remove all generated object files.
clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BOLD)$(L_RED)$(NAME) object files removed.$(RESET)"

# Rule to remove all generated object files and the program executable.
fclean:	clean
	@rm -f $(NAME) $(NAME_TEST)
	@echo "$(BOLD)$(L_RED)$(NAME) removed.$(RESET)"

# Rule to remove all generated object files, the program executable,
# and then rebuild the program.
re:	fclean all

# x_all: also removes/recompiles libft
clean_all: clean
	@make -s -C $(LIBFT_DIR) clean

fclean_all: clean fclean
	@make -s -C $(LIBFT_DIR) fclean

re_all:	fclean_all all

##########
## TEST ##
##########

NAME_TEST :=	$(NAME)_test
TEST_DIR :=		src_test
TEST_FILES :=	main_test.c \
				free_test.c \
				utils_test.c \
				parsing/parsing_test.c \
				0_init/init_cd_test.c \
				0_init/init_data_test.c \
				0_init/init_env_test.c \
				0_init/init_export_test.c
				1_check_input/check_input_test.c \
				2_tokenizer/tokenizer_test.c \
				2_tokenizer/tokenizer_redirection_test.c \
				2_tokenizer/tokenizer_pipe_test.c \
				2_tokenizer/tokenizer_utils_test.c \
				3_parser/parser_test.c \
				3_parser/parser_var_expansion_test.c \
				3_parser/parser_var_expansion_utils_test.c \
				3_parser/parser_heredoc_test.c \
				3_parser/parser_heredoc_utils_test.c \
				5_execution/errors_test.c \
				5_execution/execution_prep_test.c \
				5_execution/execution_test.c \
				5_execution/execution_utils_test.c \
				5_execution/free_functions_test.c \
				5_execution/get_flags_and_command_test.c \
				5_execution/get_path_test.c \
				5_execution/init_exec_test.c \
				5_execution/pipes_test.c \
				5_execution/redirections_check_test.c \
				5_execution/redirections_do_test.c \
				4_builtins/cd_test.c \
				4_builtins/echo_test.c \
				4_builtins/env_test.c \
				4_builtins/exit_test.c \
				4_builtins/export_test.c \
				4_builtins/export_utils_test.c \
				4_builtins/pwd_test.c \
				4_builtins/unset_test.c \
				4_builtins/errors/cd_errors_test.c \
				4_builtins/errors/env_errors_test.c \
				4_builtins/errors/exit_errors_test.c \
				4_builtins/errors/export_errors_test.c \
				4_builtins/errors/pwd_errors_test.c \
				4_builtins/errors/unset_errors_test.c \
				4_builtins/standard_functions/count_test.c \
				4_builtins/standard_functions/free_functions_test.c \
				4_builtins/standard_functions/modified_standards_test.c \

TEST_SRCS :=	$(addprefix $(TEST_DIR)/, $(TEST_FILES))
TEST_OBJS :=	$(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJS_DIR)/%.o)

# Used for progress bar
TEST_TOTAL_SRCS :=	$(words $(TEST_SRCS))
SRC_NUM :=		0

$(NAME_TEST):	$(TEST_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_FLAGS) -o $(NAME_TEST)
	@echo "$(BOLD)$(YELLOW)\n$(NAME_TEST) successfully compiled.$(RESET)"
	@echo "\nUsage: './minishell_test' to start the program, then use it like bash.\n"

# Compilation of TEST
$(OBJS_DIR)/%.o:	$(TEST_DIR)/%.c $(HDRS)
	@mkdir -p $(@D)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TEST_TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d/%d - " $(SRC_NUM) $(TEST_TOTAL_SRCS)
	@printf "%d%% $(RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -D FD_SIZE=$(FD_SIZE) -c $< -o $@

test:	$(LIBFT) $(NAME_TEST)

re_test:	fclean_all test

##############
## TEST END ##
##############

.PHONY: all clean fclean re clean_all fclean_all re_all test re_test
