CC = gcc 
CFLAGS = -fPIC -O0 -g -Wall 
LDFLAGS = -lm
IGRAPH_INCLUDE = -I /usr/local/include/igraph
IGRAPH_LIB = -L /usr/local/lib/ -ligraph

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

.PHONY: all clean
all: libc.so

libc.so: $(OBJ)
	$(CC) -shared $^ -o $@ $(LDFLAGS) $(IGRAPH_LIB)

%.o: %.c %.h
	$(CC) $(CFLAGS) $(IGRAPH_INCLUDE) -c $< -o $@

clean:
	rm -rfv *.o *.so main.e
