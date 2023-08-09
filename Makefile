CC = gcc
SRCS_GET = fips.c
SRCS_SET = fips_set.c
SRCS_TRACE = trace.c
OBJS_GET = $(SRCS_GET:.c=.o)
OBJS_SET = $(SRCS_SET:.c=.o)
OBJS_TRACE = $(SRCS_TRACE:.c=.o)
# Customize the OpenSSL to compile with.
OPENSSL_DIR = /home/jaruga/.local/openssl-3.2.0-dev-fips-debug-6d38ccedb2
OPENSSL_INC_DIR = $(OPENSSL_DIR)/include
OPENSSL_LIB_DIR = $(OPENSSL_DIR)/lib
CFLAGS = -I $(OPENSSL_INC_DIR) -L $(OPENSSL_LIB_DIR) $(OPTFLAGS) $(DEBUGFLAGS)
OPTFLAGS = -O0
DEBUGFLAGS = -g3 -ggdb3 -gdwarf-5
INCFLAGS =
LDFLAGS =

EXE = fips
EXE_SET = fips_set
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

.PHONY: run-non-fips
run-non-fips :
	OPENSSL_CONF_INCLUDE=$(OPENSSL_DIR)/ssl \
	OPENSSL_MODULES=$(OPENSSL_LIB_DIR)/ossl-modules \
	./fips

.PHONY: run-fips
run-fips :
	OPENSSL_CONF=$(OPENSSL_DIR)/ssl/openssl_fips.cnf \
	OPENSSL_CONF_INCLUDE=$(OPENSSL_DIR)/ssl \
	OPENSSL_MODULES=$(OPENSSL_LIB_DIR)/ossl-modules \
	./fips

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
