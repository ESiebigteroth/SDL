all: main.cpp
	c++ main.cpp -DHWY_SHARED_DEFINE -DAVIF_DLL -D_THREAD_SAFE -I/opt/homebrew/include/SDL2 -I/opt/homebrew/opt/libpng/include/libpng16 -I/opt/homebrew/Cellar/jpeg-xl/0.11.0/include -I/opt/homebrew/Cellar/highway/1.2.0/include -I/opt/homebrew/Cellar/brotli/1.1.0/include -I/opt/homebrew/Cellar/jpeg-xl/0.11.0/include -I/opt/homebrew/Cellar/little-cms2/2.16/include -I/opt/homebrew/Cellar/libtiff/4.7.0/include -I/opt/homebrew/opt/zstd/include -I/opt/homebrew/Cellar/xz/5.6.2/include -I/opt/homebrew/Cellar/jpeg-turbo/3.0.4/include -I/opt/homebrew/Cellar/libavif/1.1.1/include -I/opt/homebrew/Cellar/aom/3.10.0/include -I/opt/homebrew/Cellar/libvmaf/3.0.0/include -I/opt/homebrew/Cellar/libvmaf/3.0.0/include/libvmaf -I/opt/homebrew/Cellar/webp/1.4.0/include -I/opt/homebrew/Cellar/webp/1.4.0/include/webp -I/opt/homebrew/include -I/opt/homebrew/include/SDL2 -L/opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib -L/opt/homebrew/lib -lSDL2_image -lSDL2 -o main


clean:
	rm -f main