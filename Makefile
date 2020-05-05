windows:
	gcc -Iinclude/ src/* -lSOIL -lobj -lglut32 -lopengl32 -lglu32 -lm -o chess.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/* -lSOIL -lobj -lGL -lGLU -lglut -lm -o chess -Wall -Wextra -Wpedantic
