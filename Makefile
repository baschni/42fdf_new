NAME = fdf

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a
LIBX_DIR=libx
LIBX=$(LIBX_DIR)/libmlx.a

SRC_DIR=code
INCL_DIR=head
OBJ_DIR=obj

SOURCES:=main.c map.c map2.c free.c edge.c scene.c scene2.c edges_from_map.c \
vector.c vector2.c vector3.c vector4.c vector5.c vector6.c vector7.c \
print_line.c print_pixel.c render.c render2.c move_camera_bonus.c view_and_canvas.c \
events_bonus.c events_bonus2.c debug.c
SOURCES:=$(addprefix $(SRC_DIR)/, $(SOURCES))
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES=-I$(INCL_DIR) -I$(LIBFT_DIR) -I$(LIBX_DIR)
LIBRARIES=-lXext -lX11 -lz -lm -lpthread -static-libasan 

CC=gcc
CFLAGS=-Wextra -Werror -Wall -pthread -O3#-O3 #-g -fsanitize=thread # -O3

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)

$(LIBFT):
	make -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)" CC="$(CC)"

$(OBJECTS): $(SOURCES)
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	$(CC) $(CFLAGS) -c -o $@ ${@:$(OBJ_DIR)%.o=$(SRC_DIR)%.c} $(INCLUDES)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ_DIR)/*

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -f $(OBJ_DIR)/*
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all