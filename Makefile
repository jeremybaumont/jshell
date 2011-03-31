HOME=/home/jeremyb
CSCOPE_HOME=$(HOME)/devel/cscope
LNX=$(HOME)/devel/unix/brown/assignment/shell

CC=gcc
DEBUG?=0
ifeq ($(DEBUG), 1)
	CFLAGS=-Wall -g -DDEBUG
else
	CFLAGS=-Wall 
endif

SOURCES=parse.c shell.c
OBJECTS=$(SOURCES:.c=.o)
EXEC=jshell

cscope-data-files:
	cd / && find  $(LNX)                                                                \
	-path "$(LNX)/tmp*" -prune -o                                           \
	-path "$(LNX)/Documentation*" -prune -o                                 \
	-name "*.[chxsS]" -print >$(CSCOPE_HOME)/cscope.files

cscope-database: cscope-data-files
	cd $(CSCOPE_HOME) && cscope -b -q -k -i$(CSCOPE_HOME)/cscope.files

cscope: cscope-database


%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(EXEC) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

all: $(SOURCES) $(EXEC)

clean:
	rm *.o
	rm $(EXEC)
