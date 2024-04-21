SRCS = saxpy.c
TARG = saxpy.out
OBJS = $(SRCS:.c=.o)

CC = gcc
OPTS = -Wall
LIBS = -lpthread

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    OPTS += -g -DDEBUG
endif

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@ 

clean:
	rm -f $(OBJS) $(TARG) *~