GCC = gcc
SRC = matrix.c main.c
IDIR = headers
#OBJS := $(patsubst %.c, build/%.o, $(SRC))
#OBJ_MAIN = build/main.o
CFLAGS = -I$(IDIR)  -std=c11 -ggdb -Wall -Wextra -pedantic

.PHONY: RUN clean 

all: 
	mkdir -p build
	make output

output: $(SRC)
	$(GCC) -o $@ $^ $(CFLAGS)



clean:
	rm -rf output  
