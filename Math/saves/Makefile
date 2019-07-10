GCC = gcc #define the C compiler to use
SRC = matrix.c #the c fiels to be compiled
IDIR = headers
OBJS := $(patsubst %.c, build/%.o, $(SRC))
OBJ_MAIN = build/main.o
CFLAGS = -I$(IDIR) -ggdb -std=c11 -Wall -Wextra -pedantic
all:
	mkdir -p build
	make math
build/%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<
build/%.%.o: %.%.c
	$(GCC) $(CFLAGS) -c -o $@ $<
math: $(OBJ_MAIN) $(OBJS)
	$(GCC) $(OBJ_MAIN) $(OBJS) $(CFLAGS) -o  math # -lm 
clean:
	rm -rf build math
