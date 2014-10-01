CC := gcc
CFLAGS := -w -fPIC -shared -rdynamic
LDFLAGS := -ldl -lrt

LIB := interpose.so
SRC := temp.c

all:
	$(CC) $(CFLAGS) -o $(LIB) $(SRC) $(LDFLAGS)

clean:
	rm -f $(LIB)
