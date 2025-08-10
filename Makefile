NAME = minishell

UTILS = utils/utils.a
UTILS_DIR = utils/

CC = cc
CFLAGS = -Wall -Werror -Wextra -g 

SRC = other_utils/close.c \
	main.c \
	other_utils/matrix_utils.c \
	parsing/parsing.c \
	parsing/count_words.c \
	parsing/matrix_handler.c \
	parsing/matrix_handler_utils.c \
	parsing/quotes_core.c \
	commands/commands_hub.c \
	commands/builtin_commands/other_builtin.c \
	commands/builtin_commands/other_builtin_2.c \
	commands/builtin_commands/cd/ft_cd.c \
	parsing/parsing_utils.c \
	parsing/parsing_utils_2.c \
	parsing/parsing_utils_3.c \
	parsing/parsing_utils_4.c \
	parsing/parsing_utils_5.c \
	commands/exec.c \
	commands/exec_utils.c \
	commands/exec_utils_2.c \
	commands/exec_utils_3.c \
	commands/exec_utils_4.c \
	commands/get_path_commands.c \
	commands/get_path_commands_utils.c \
	commands/builtin_commands/export/ft_export.c \
	commands/builtin_commands/export/ft_export_utils_1.c \
	commands/builtin_commands/export/ft_export_utils_2.c \
	commands/builtin_commands/export/ft_export_utils_3.c \
	commands/builtin_commands/unset/ft_unset.c \
	commands/builtin_commands/unset/ft_unset_utils.c \
	commands/builtin_commands/unset/ft_unset_utils_2.c \
	commands/builtin_commands/echo/ft_echo.c \
	commands/builtin_commands/echo/ft_echo_utils.c \
	commands/builtin_commands/echo/ft_echo_utils_2.c \
	commands/builtin_commands/echo/ft_echo_utils_3.c \
	commands/builtin_commands/cd/ft_cd_utils_1.c \
	commands/builtin_commands/cd/ft_cd_utils_2.c \
	commands/builtin_commands/cd/ft_cd_utils_3.c \
	commands/builtin_commands/cd/ft_cd_utils_4.c \
	commands/non_builtin_commands/fork.c \
	commands/non_builtin_commands/fork_2.c \
	globals/global.c \
	redirections/here_doc.c \
	redirections/here_doc_utils.c \
	redirections/here_doc_utils_2.c \
	redirections/expansion_in_hd.c \
	other_utils/signals.c \
	main_utils.c \
	main_utils_2.c \
	main_utils_3.c \
	main_utils_4.c \
	ft_atol.c \
	redirections/manage_in_out.c \
	redirections/manage_input.c \
	redirections/manage_input_utils.c \
	redirections/manage_output.c \
	parsing/parsing_checks.c \
	parsing/parsing_checks_utils.c \

all: $(NAME)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(UTILS):
	$(MAKE) -C $(UTILS_DIR)

$(NAME): $(PRINTF) $(UTILS)
	$(CC) $(CFLAGS) $(SRC) $(UTILS) -lreadline -o $(NAME)

clean:
	rm -f

fclean: clean
	rm -f $(NAME)
	
re: fclean $(NAME)

.PHONY: all clean fclean re

