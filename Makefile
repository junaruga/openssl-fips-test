CC = gcc
SRCS_GET = fips_mode.c
SRCS_SET = fips_mode_set.c
SRCS_TRACE = trace.c
CFLAGS = $(OPTFLAGS) $(DEBUGFLAGS)
OPTFLAGS = -O0
DEBUGFLAGS = -g3 -ggdb3 -gdwarf-5
INCFLAGS =
LDFLAGS =
OBJS_GET = $(SRCS_GET:.c=.o)
OBJS_SET = $(SRCS_SET:.c=.o)
OBJS_TRACE = $(SRCS_TRACE:.c=.o)

EXE = fips_mode
EXE_SET = fips_mode_set
EXE_TRACE = trace
EXE_ALL= $(EXE) $(EXE_SET) $(EXE_TRACE)
LIBS = -lssl -lcrypto

.c.o :
	$(CC) -c $(CFLAGS) $(INCFLAGS) $< -o $@

.PHONY: all
all : $(EXE) $(EXE_SET) $(EXE_TRACE)

$(EXE) : $(OBJS_GET)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(EXE_SET) : $(OBJS_SET)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(EXE_TRACE) : $(OBJS_TRACE)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean :
	rm -f *.o $(EXE_ALL)

.PHONY: test
test :
	@echo "Testing..."
	ldd ./$(EXE)
	./$(EXE)

.PHONY: test-set
test-set :
	@echo "Testing..."
	./$(EXE_SET)

.PHONY: test-trace
test-trace :
	@echo "Testing..."
	./$(EXE_TRACE)

.PHONY: test-strace
strace-test :
	@echo "Testing with strace..."
	strace ./$(EXE)
