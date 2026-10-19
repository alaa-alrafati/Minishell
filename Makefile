NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
READLINE_FLAGS = -lreadline

MINISHELL_DIR = minishell_project

MINISHELL_FILES = main.c utils.c main_utils.c

BUILTINS_FILES = built_in_cmd/built_in_cmd.c built_in_cmd/built_in_export.c built_in_cmd/built_in_export2.c \
				built_in_cmd/built_in_helper.c built_in_cmd/built_in_cd.c built_in_cmd/built_in_unset.c \
				built_in_cmd/built_in_exit.c built_in_cmd/built_in_controller.c

PARSER_FILES = parsing/expand.c parsing/expand_utils.c parsing/lexer.c parsing/lexer_words_handle.c parsing/parser_handle_heredoc.c \
				parsing/parser_utils_2.c parsing/parser.c parsing/parser_utils.c

EXECUTE_FILES = execution/execute.c execution/fill_env_struct.c execution/helper_function.c \
				execution/convert_env_to_array.c execution/cmd_path.c execution/cmd_path_utils.c \
				execution/execution_controller.c execution/execute_utils.c execution/execute_utils2.c

ALL_FILES = $(MINISHELL_FILES) $(BUILTINS_FILES) $(PARSER_FILES) $(EXECUTE_FILES)

SRC = $(addprefix $(MINISHELL_DIR)/, $(ALL_FILES))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME) :$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(READLINE_FLAGS) -o $(NAME)
clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
