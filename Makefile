# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natalierh <natalierh@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 11:14:10 by aschenk           #+#    #+#              #
#    Updated: 2024/05/25 10:51:37 by natalierh        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			minishell

SRCS_DIR :=		src
SRCS :=			$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/free.c \
				$(SRCS_DIR)/builtins/builtin_struct_inits.c \
				$(SRCS_DIR)/builtins/cd.c \
				$(SRCS_DIR)/builtins/pwd.c \
				$(SRCS_DIR)/errors/print_error.c \
				$(SRCS_DIR)/parsing/parsing.c \
				$(SRCS_DIR)/standard_functions/count.c \
				$(SRCS_DIR)/standard_functions/free_functions.c \
				$(SRCS_DIR)/standard_functions/modified_standards.c

OBJS_DIR :=		obj
OBJS :=			$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

HDRS_DIR :=		include
HDRS := 		$(HDRS_DIR)/minishell.h \
				$(HDRS_DIR)/config.h \
				$(HDRS_DIR)/tokenizer.h \
				$(HDRS_DIR)/errors.h

# LIBFT
LIBFT_DIR :=	libft
LIBFT_FLAGS :=	-L$(LIBFT_DIR) -lft -lreadline -lhistory
LIBFT :=		$(LIBFT_DIR)/libft.a

# OTHER LIBS
LIB_FLAGS :=	$(LIBFT_FLAGS)

CC :=			cc
CFLAGS :=		-Wall -Werror -Wextra -I$(HDRS_DIR) -I$(LIBFT_DIR)
CFLAGS +=		-Wpedantic -g
#CFLAGS +=		-fsanitize=address

# Used for progress bar
TOTAL_SRCS :=	$(words $(SRCS))
SRC_NUM :=		0

# Define ANSI escape codes for colors and styles
RESET =			\033[0m
BOLD =			\033[1m
RED =			\033[31;2m
GREEN =			\033[32m
YELLOW =		\033[33m
L_RED :=		\033[91m
ORANGE :=		\033[38;5;208m
BLUE := 		\033[34m
VIOLET := 		\033[35;1m

LOGO :=			"$(BOLD)$(L_RED) _  _   $(ORANGE)__   $(YELLOW)__ _   $(GREEN)__   $(BLUE)____   $(VIOLET)_  _   $(L_RED)____   $(ORANGE)__     $(YELLOW)__   \n$(L_RED)( \\/ ) $(ORANGE)(  ) $(YELLOW)(  ( \\ $(GREEN)(  ) $(BLUE)/ ___) $(VIOLET)/ )( \\ $(L_RED)(  __) $(ORANGE)(  )   $(YELLOW)(  )  \n$(L_RED)/ \\/ \\  $(ORANGE))(  $(YELLOW)/    /  $(GREEN))(  $(BLUE)\\___ \\ $(VIOLET)) __ (  $(L_RED)) _)  $(ORANGE)/ (_/\\ $(YELLOW)/ (_/\\ \n$(L_RED)\\_)(_/ $(ORANGE)(__) $(YELLOW)\\_)__) $(GREEN)(__) $(BLUE)(____/ $(VIOLET)\\_)(_/ $(L_RED)(____) $(ORANGE)\\____/ $(YELLOW)\\____/\n\n$(RESET)$(BOLD)by Natalie Holbrook & Alex Schenk @42 Berlin, June 2024\n$(RESET)"

# target
all:			$(LIBFT) $(NAME)

# Build libft library by calling 'make' in LIBFT_DIR.
# This target will be executed if libft.a is missing or
# if any of the listed .c or .h files in LIBFT_DIR are modified.
$(LIBFT):	$(LIBFT_DIR)/libft.h \
			$(LIBFT_DIR)/ft_isalpha.c \
			$(LIBFT_DIR)/ft_isdigit.c \
			$(LIBFT_DIR)/ft_isalnum.c \
			$(LIBFT_DIR)/ft_isascii.c \
			$(LIBFT_DIR)/ft_isprint.c \
			$(LIBFT_DIR)/ft_strlen.c \
			$(LIBFT_DIR)/ft_toupper.c \
			$(LIBFT_DIR)/ft_tolower.c \
			$(LIBFT_DIR)/ft_strncmp.c \
			$(LIBFT_DIR)/ft_strlcpy.c \
			$(LIBFT_DIR)/ft_strlcat.c \
			$(LIBFT_DIR)/ft_strchr.c \
			$(LIBFT_DIR)/ft_strrchr.c \
			$(LIBFT_DIR)/ft_strnstr.c \
			$(LIBFT_DIR)/ft_memset.c \
			$(LIBFT_DIR)/ft_memchr.c \
			$(LIBFT_DIR)/ft_memcpy.c \
			$(LIBFT_DIR)/ft_memcmp.c \
			$(LIBFT_DIR)/ft_memmove.c \
			$(LIBFT_DIR)/ft_bzero.c \
			$(LIBFT_DIR)/ft_atoi.c \
			$(LIBFT_DIR)/ft_strdup.c \
			$(LIBFT_DIR)/ft_calloc.c \
			$(LIBFT_DIR)/ft_substr.c \
			$(LIBFT_DIR)/ft_strjoin.c \
			$(LIBFT_DIR)/ft_strtrim.c \
			$(LIBFT_DIR)/ft_split.c \
			$(LIBFT_DIR)/ft_itoa.c \
			$(LIBFT_DIR)/ft_strmapi.c \
			$(LIBFT_DIR)/ft_striteri.c \
			$(LIBFT_DIR)/ft_putchar_fd.c \
			$(LIBFT_DIR)/ft_putstr_fd.c \
			$(LIBFT_DIR)/ft_putendl_fd.c \
			$(LIBFT_DIR)/ft_putnbr_fd.c \
			$(LIBFT_DIR)/ft_lstnew.c \
			$(LIBFT_DIR)/ft_lstadd_front.c \
			$(LIBFT_DIR)/ft_lstsize.c \
			$(LIBFT_DIR)/ft_lstlast.c \
			$(LIBFT_DIR)/ft_lstadd_back.c \
			$(LIBFT_DIR)/ft_lstdelone.c \
			$(LIBFT_DIR)/ft_lstclear.c \
			$(LIBFT_DIR)/ft_lstiter.c \
			$(LIBFT_DIR)/ft_lstmap.c \
			$(LIBFT_DIR)/ft_strcmp.c \
			$(LIBFT_DIR)/ft_isbinary.c \
			$(LIBFT_DIR)/get_next_line_bonus.c \
			$(LIBFT_DIR)/ft_printf_utils.c \
			$(LIBFT_DIR)/ft_printf.c \
			$(LIBFT_DIR)/ft_atoi_base.c
	@make -s -C $(LIBFT_DIR)
	@echo ""

# Target $(NAME) depends on object files $(OBJS) and libft library.
$(NAME):	$(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(YELLOW)\n$(NAME) successfully compiled.$(RESET)"
	@echo $(LOGO)
	@echo "Usage: './minishell' to start the program, then use it like bash.\n"

# COMPILATION PROGRESS BAR
# Rule to define how to generate object files (%.o) from corresponding
# source files (%.c). Each .o file depends on the associated .c file and the
# project header file (include/project.h)
# -c:		Generates o. files without linking.
# -o $@:	Output file name;  '$@' is replaced with target name (the o. file).
# -$<:		Represents the first prerequisite (the c. file).
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

# Target to remove all generated files.
clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BOLD)$(RED)$(NAME) object files removed.$(RESET)"

# Target to remove all generated files and the program executable.
fclean:	clean
	@rm -f $(NAME) $(NAME_TEST)
	@echo "$(BOLD)$(RED)$(NAME) removed.$(RESET)"

# Target to remove all generated files, the program executable,
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
TEST_SRCS :=	$(TEST_DIR)/main_test.c \
  				$(TEST_DIR)/free_test.c \
				$(TEST_DIR)/utils_test.c \
				$(TEST_DIR)/0_tokenizer/tokenizer_get_tokens_test.c \
				$(TEST_DIR)/0_tokenizer/tokenizer_redirection_test.c \
				$(TEST_DIR)/0_tokenizer/tokenizer_utils_test.c \
				$(TEST_DIR)/builtins/builtin_struct_inits_test.c \
				$(TEST_DIR)/builtins/cd_test.c \
				$(TEST_DIR)/builtins/pwd_test.c \
				$(TEST_DIR)/builtins/exit_test.c \
				$(TEST_DIR)/errors/print_error_test.c \
				$(TEST_DIR)/parsing/parsing_test.c \
				$(TEST_DIR)/standard_functions/count_test.c \
				$(TEST_DIR)/standard_functions/free_functions_test.c \
				$(TEST_DIR)/standard_functions/modified_standards_test.c

TEST_OBJS :=	$(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJS_DIR)/%.o)

# Used for progress bar
TEST_TOTAL_SRCS :=	$(words $(TEST_SRCS))
SRC_NUM :=		0

$(NAME_TEST):	$(TEST_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_FLAGS) -o $(NAME_TEST)
	@echo "$(BOLD)$(YELLOW)\n$(NAME_TEST) successfully compiled.$(RESET)"
	@echo $(LOGO)
	@echo "Usage: './minishell_test' to start the program, then use it like bash.\n"

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
