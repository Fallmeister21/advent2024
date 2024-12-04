CC = clang++
CCFLAGS = -g -O0 -Wall -pedantic -Wlong-long `sdl2-config --cflags` #-fsanitize=address --fno-omit-frame-pointer
CCOPTS+= -D_LINUX -DDEBUGGING_ON

SRC = $(wildcard *.cpp)
HDR = $(wildcard *.h)
OBJ = $(SRC: .cpp=.o)

Day1: $(OBJ)
	$(CC) $(CCFLAGS) $(CCOPTS) $^ -o $@

clean:
	rm -f Day1