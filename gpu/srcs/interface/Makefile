# Flags
CFLAGS = -std=c99 -pedantic -O2
LIBS :=

GLFW3 = /Users/svilau/brew/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib

GLEW = /Users/svilau/brew/Cellar/glew/2.1.0/lib/libGLEW.a

ifeq ($(OS),Windows_NT)
BIN := $(BIN).exe
	LIBS := -lglfw3 -lopengl32 -lm -lGLU32 -lGLEW32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LIBS := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
#		LIBS := GLEW GLFW3
		CFLAGS += -I/usr/local/include
	else
		LIBS := -lGL -lm -lGLU
#		LIBS := GLEW GLFW3
	endif
endif

all: generate file_browser extended canvas skinning

generate: clean
ifeq ($(OS),Windows_NT)
	@mkdir bin 2> nul || exit 0
else
	@mkdir -p bin	
endif

clean:
	@rm -rf bin

file_browser: generate
	$(CC) $(CFLAGS) -o bin/file_browser file_browser.c -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo $(GLEW) $(GLFW3)

extended: generate
	$(CC) $(CFLAGS) -o bin/extended extended.c -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo $(GLEW) $(GLFW3)

canvas: generate
	$(CC) $(CFLAGS) -o bin/canvas canvas.c -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo $(GLEW) $(GLFW3)

skinning: generate
	$(CC) $(CFLAGS) -o bin/skinning skinning.c -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo $(GLEW) $(GLFW3)

