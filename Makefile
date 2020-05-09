FLAGS:=

ifeq ($(OS),Windows_NT)
	FLAGS=-lglut32 -lopengl32 -lglu32
else
	FLAGS=-lGL -lGLU -lglut
endif

all:
	gcc -Iinclude/ src/* -lSOIL -lobj $(FLAGS) -lm -o chess -Wall -Wextra -Wpedantic
