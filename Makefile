main: main.cpp
	c++ main.cpp `pkg-config --cflags --libs sdl2 SDL2_image` -o main


clean:
	rm -f main