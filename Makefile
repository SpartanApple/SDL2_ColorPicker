OBJ = sdlcolorwheel.c

CC = gcc

FLAGS = -lm -lSDL2 -lSDL2_ttf

OBJ_NAME = colorSelector

all : $(OBJS)
		$(CC) $(OBJ) $(FLAGS) -o $(OBJ_NAME)

clean:
		rm $(OBJ_NAME)



