NAME		= libft.a

GCC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

AR			= ar rcs

SRC_FILES	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c get_next_line.c ft_printf.c ft_printf_utils.c ft_printf_helper.c ft_printf_parsing.c \
			 ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			 ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
			 ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ_DIR		= objs/

OBJ_FILES	= $(SRC_FILES:%.c=%.o)

GREEN		= \033[0;32m
PURPLE		= \033[0;35m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
			@$(AR) $(NAME) $(OBJ_FILES)
			@printf "$(GREEN)$(NAME) Created!\n $(RESET)"

%.o: %.c
			@$(GCC) $(CFLAGS) -c $< -o $@
			@printf "$(PURPLE)$< compiled!\n $(RESET)" 

clean: 
			@$(RM) $(OBJ_FILES) $(OBJ_BONUS)
			@printf "$(PURPLE)Cleaned object files!\n$(RESET)"

fclean: clean
			@$(RM) $(NAME)
			@printf "$(PURPLE)Cleaned library and object files!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re