NAME = fdf

LIBFT_DIR=libft
LIBFT=$(LIBFT_DIR)/libft.a

LIBX_DIR=libx
LIBX=$(LIBX_DIR)/libmlx.a

SRC_DIR=code
INCL_DIR=head
OBJ_DIR=obj

SRC_DIR_BONUS=code_bonus
INCL_DIR_BONUS=head_bonus
OBJ_DIR_BONUS=obj_bonus

SOURCES:=main.c map.c map2.c free.c edge.c scene.c scene2.c edges_from_map.c \
vector.c vector2.c vector3.c vector4.c vector5.c vector6.c vector7.c \
print_line.c print_pixel.c render.c render2.c view_and_canvas.c \
events.c
SOURCES:=$(addprefix $(SRC_DIR)/, $(SOURCES))
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


SOURCES_BONUS:=main.c map.c map2.c free.c edge.c scene.c scene2.c edges_from_map.c \
vector.c vector2.c vector3.c vector4.c vector5.c vector6.c vector7.c \
print_line.c print_pixel.c render.c render2.c move_camera_bonus.c move_camera_bonus2.c move_camera_bonus3.c view_and_canvas.c \
events_bonus.c
SOURCES_BONUS:=$(addprefix $(SRC_DIR_BONUS)/, $(SOURCES_BONUS))
OBJECTS_BONUS=$(SOURCES_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

INCLUDES=-I$(LIBFT_DIR) -I$(LIBX_DIR)
LIBRARIES=-lXext -lX11 -lz -lm

CC=gcc
CFLAGS=-Wextra -Werror -Wall -pthread -Ofast


$(NAME): $(OBJECTS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARIES)

bonus: $(OBJECTS_BONUS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) -o $(NAME)_bonus $^ $(LIBRARIES) -lpthread
	
$(OBJECTS): $(SOURCES)
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	$(CC) $(CFLAGS) -c -o $@ ${@:$(OBJ_DIR)%.o=$(SRC_DIR)%.c} $(INCLUDES) -I$(INCL_DIR)

$(OBJECTS_BONUS): $(SOURCES_BONUS)
	@if [ ! -d $(OBJ_DIR_BONUS) ]; then mkdir $(OBJ_DIR_BONUS); fi
	$(CC) $(CFLAGS) -c -o $@ ${@:$(OBJ_DIR_BONUS)%.o=$(SRC_DIR_BONUS)%.c} $(INCLUDES) -I$(INCL_DIR_BONUS)

all: $(NAME) bonus

$(LIBFT):
	make -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)" CC="$(CC)"

$(LIBX):
	make -C $(LIBX_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBX_DIR)
	rm -f $(OBJ_DIR)/*
	rm -f $(OBJ_DIR_BONUS)/*

fclean:
	make fclean -C $(LIBFT_DIR)
	make clean -C $(LIBX_DIR)
	rm -f $(OBJ_DIR)/*
	rm -f $(OBJ_DIR_BONUS)/*
	rm -f $(NAME)
	rm -f $(NAME)_bonus

re: fclean all

.PHONY: clean fclean re all