NAME			=	minishell

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -f
AR				=	ar -rcs

SRCS			=	src/minishell.c \
					src/pipes.c \
					src/pipe_utils.c \
					src/error.c \
					src/free.c \
					src/checker.c \
					src/split_pipex.c \
					src/utils_checker.c \
					src/utils_redirect.c 
					
					

#		COLORS		#
CYELLOW			=\033[1;33m
CGREEN			=\033[0;32m
CRED			=\033[0;91m
PURPLE			=\033[0;35m
CRESET			=\033[0m

OBJS			=	$(SRCS:.c=.o)

LIBFT = libft/libft.a

%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@

all:			$(LIBFT) $(NAME)

$(LIBFT):
				@make -C ./libft

$(NAME):		$(OBJS)
				@$(CC) $(FLAGS) $(LIBFT) $(OBJS)   -o $(NAME) -lreadline
				@echo "\n$(CYELLOW)$(NAME) $(PURPLE)-> $(CGREEN) compiled$(CRESET)"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_B)
				@make -C ./libft clean
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} objects files were deleted.${CRESET}"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_B)
				@make -C ./libft fclean
				@echo "${CYELLOW}${NAME} $(PURPLE)-> ${CRED} was deleted.${CRESET}"

re:				fclean all

.PHONY:			all clean fclean re