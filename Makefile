CC = gcc
SRCS = fips_mode.c
CFLAGS =
LDFLAGS = -g
OBJS = $(SRCS:.c=.o)
EXE = fips_mode
LIBS = -lssl -lcrypto

.c.o :
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: all
all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean :
	rm -f *.o $(EXE)

.PHONY: test
test :
	@echo "Testing..."
	./$(EXE)
