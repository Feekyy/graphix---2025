all:
	del main.exe
	cls
	gcc -Iinclude/ -Iassets src/main.c src/app.c src/scene.c src/draw.c src/objlist.c -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -g
clean:
	del main.exe
	cls
debug:
	del main.exe
	cls
	gcc -Iinclude/ -Iassets src/main.c src/app.c src/scene.c src/draw.c src/objlist.c -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -g
	dbg main.exe
