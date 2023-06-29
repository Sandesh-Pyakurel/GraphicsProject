
OBJS = src/*.cpp

CC = g++

INCLDUE_PATHS = -I include -I include/headers

LIBRARY_PATHS = -L include/lib

COMPILER_FLAGS = -w

LINKER_FLAGS = -lglfw -lGLEW -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl 

OBJ_NAME = main glad.o

all: $(OBJS)
	$(CC) $(OBJS) $(INCLDUE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
