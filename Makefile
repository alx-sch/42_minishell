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

HISTORY_FILE = .minishell_history

# SOURCE FILES
SRCS_DIR :=		src
SRCS_FILES :=	0_init/init_cd.c \
				0_init/init_data.c \
				0_init/init_env.c \
				0_init/init_export.c \
				1_check_input/check_input.c \
				2_tokenizer/tokenizer.c \
				2_tokenizer/tokenizer_redirection.c \
				2_tokenizer/tokenizer_pipe.c \
				2_tokenizer/tokenizer_utils.c \
				3_parser/parser.c \
				3_parser/parser_utils.c \
				3_parser/parser_var_expansion.c \
				3_parser/parser_var_expansion_utils.c \
				3_parser/parser_heredoc.c \
				3_parser/parser_heredoc_utils.c \
				4_builtins/builtin.c \
				4_builtins/builtin_utils.c \
				4_builtins/builtins/cd.c \
				4_builtins/builtins/echo.c \
				4_builtins/builtins/env.c \
				4_builtins/builtins/exit.c \
				4_builtins/builtins/export.c \
				4_builtins/builtins/export_utils.c \
				4_builtins/builtins/pwd.c \
				4_builtins/builtins/unset.c \
				4_builtins/errors/cd_errors.c \
				4_builtins/errors/env_errors.c \
				4_builtins/errors/exit_errors.c \
				4_builtins/errors/export_errors.c \
				4_builtins/errors/pwd_errors.c \
				4_builtins/errors/unset_errors.c \
				4_builtins/utils/count_array_length.c \
				4_builtins/utils/free_functions.c \
				4_builtins/utils/modified_standards.c \
				5_execution/execution/execution_only_parent.c \
				5_execution/execution/execution.c \
				5_execution/execution_prep/child_processes.c \
				5_execution/execution_prep/execution_prep.c \
				5_execution/execution_prep/execution_utils.c \
				5_execution/execution_prep/get_flags_and_command.c \
				5_execution/execution_prep/get_path.c \
				5_execution/execution_prep/pipes.c \
				5_execution/execution_prep/redirections_check.c \
				5_execution/execution_prep/redirections_do.c \
				5_execution/utils/errors.c \
				5_execution/utils/free_functions.c \
				5_execution/init_exec.c \
				6_signals/signals_prompts.c \
				6_signals/signals_execution.c \
				6_signals/signals_eot.c \
				7_utils/free.c \
				7_utils/logo.c \
				7_utils/errors.c \
				7_utils/utils.c \
				8_history/history.c \
				main.c

SRCS :=			$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

# OBJECT FILES
OBJS_DIR :=		obj
OBJS :=			$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# HEADER FILES
HDRS_DIR :=		include
HDRS_FILES := 	builtins.h \
				config.h \
				errors.h \
				execution.h \
				init.h \
				input_check.h \
				minishell.h \
				parser.h \
				signals.h \
				tokenizer.h \
				types.h


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
# CFLAGS +=		-fsanitize=address

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

# Rule to remove all generated object files and the program executable and the command history file.
fclean:	clean
	@rm -f $(NAME) $(NAME_TEST)
	@echo "$(BOLD)$(L_RED)$(NAME) removed.$(RESET)"
	@rm -f $(HISTORY_FILE)
	@echo "$(BOLD)$(L_RED)$(HISTORY_FILE) removed.$(RESET)"

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
TEST_FILES :=	0_init/init_cd_test.c \
				0_init/init_data_test.c \
				0_init/init_env_test.c \
				0_init/init_export_test.c \
				1_check_input/check_input_test.c \
				2_tokenizer/tokenizer_test.c \
				2_tokenizer/tokenizer_redirection_test.c \
				2_tokenizer/tokenizer_pipe_test.c \
				2_tokenizer/tokenizer_utils_test.c \
				3_parser/parser_test.c \
				3_parser/parser_utils_test.c \
				3_parser/parser_var_expansion_test.c \
				3_parser/parser_var_expansion_utils_test.c \
				3_parser/parser_heredoc_test.c \
				3_parser/parser_heredoc_utils_test.c \
				4_builtins/builtin_test.c \
				4_builtins/builtin_utils_test.c \
				4_builtins/builtins/cd_test.c \
				4_builtins/builtins/echo_test.c \
				4_builtins/builtins/env_test.c \
				4_builtins/builtins/exit_test.c \
				4_builtins/builtins/export_test.c \
				4_builtins/builtins/export_utils_test.c \
				4_builtins/builtins/pwd_test.c \
				4_builtins/builtins/unset_test.c \
				4_builtins/errors/cd_errors_test.c \
				4_builtins/errors/env_errors_test.c \
				4_builtins/errors/exit_errors_test.c \
				4_builtins/errors/export_errors_test.c \
				4_builtins/errors/pwd_errors_test.c \
				4_builtins/errors/unset_errors_test.c \
				4_builtins/utils/count_array_length_test.c \
				4_builtins/utils/free_functions_test.c \
				4_builtins/utils/modified_standards_test.c \
				5_execution/execution/execution_only_parent_test.c \
				5_execution/execution/execution_test.c \
				5_execution/execution_prep/child_processes_test.c \
				5_execution/execution_prep/execution_prep_test.c \
				5_execution/execution_prep/execution_utils_test.c \
				5_execution/execution_prep/get_flags_and_command_test.c \
				5_execution/execution_prep/get_path_test.c \
				5_execution/execution_prep/pipes_test.c \
				5_execution/execution_prep/redirections_check_test.c \
				5_execution/execution_prep/redirections_do_test.c \
				5_execution/utils/errors_test.c \
				5_execution/utils/free_functions_test.c \
				5_execution/init_exec_test.c \
				6_signals/signals_prompts_test.c \
				6_signals/signals_execution_test.c \
				6_signals/signals_exit_test.c \
				7_utils/free_test.c \
				7_utils/logo_test.c \
				7_utils/errors_test.c \
				7_utils/utils_test.c \
				8_history/history_test.c \
				main_test.c

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
