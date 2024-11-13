NAME=libft.a

PRINTF_DIR=printf

BASE_SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
BASE_OBJECTS = $(patsubst %.c, %.o, $(BASE_SOURCES))

ADDITIONAL_SOURCES = ft_atol.c ft_htol.c ft_isspace.c ft_is_int_str.c ft_is_hex_str.c ft_cancel_newline_at_end.c \
auto_free.c auto_free2.c
ADDITIONAL_OBJECTS = $(patsubst %.c, %.o, $(ADDITIONAL_SOURCES))

GNL_SOURCES = get_next_line.c ft_stpcpy.c ft_join_list_to_str.c
GNL_OBJECTS = $(patsubst %.c, %.o, $(GNL_SOURCES))

PRINTF_SOURCES := ft_printf.c inner_length.c output_general.c output_general2.c \
output_hex_int_ptr.c output_str_char.c parse_format_str.c split_format_str.c free_spec.c
PRINTF_SOURCES := $(addprefix $(PRINTF_DIR)/, $(PRINTF_SOURCES))
PRINTF_OBJECTS = $(patsubst %.c, %.o, $(PRINTF_SOURCES))

CC=gcc
CFLAGS=-Wextra -Werror -Wall
OBJECTS=$(BASE_OBJECTS) $(ADDITIONAL_OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)


all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $^

$(GNL_OBJECTS) $(BASE_OBJECTS) $(ADDITIONAL_OBJECTS): $(GNL_SOURCES) $(BASE_SOURCES) $(ADDITIONAL_SOURCES)
	$(CC) $(CFLAGS) -c -o $@ $(patsubst %.o, %.c, $@)
	
$(PRINTF_OBJECTS): $(PRINTF_SOURCES)
	$(CC) $(CFLAGS) -c -o $@ $(patsubst %.o, %.c, $@) -I$(PRINTF_DIR) -I.

clean:
	rm -f *.o
	rm -f $(PRINTF_DIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
