OBJ = sdlcolorwheel.c

CC = gcc

FLAGS = -lm $(shell pkg-config --libs --cflags SDL2 SDL2_ttf)

OBJ_NAME = colorSelector

all : $(OBJS)
		$(CC) $(OBJ) $(FLAGS) -o $(OBJ_NAME)

clean:
		rm $(OBJ_NAME)



