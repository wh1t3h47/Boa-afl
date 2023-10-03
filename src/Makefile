.SUFFIXES:
.SUFFIXES: .o .c
.PHONY: clean mrclean distclean depend all dist

AFL_CC = /home/skid/AFLplusplus/afl-clang-fast
GCC_FLAGS = -Wstrict-prototypes -Wpointer-arith -Wcast-align -Wcast-qual\
  -Wtraditional\
  -Wshadow\
  -Wconversion\
  -Waggregate-return\
  -Wmissing-prototypes\
  -Wnested-externs\
  -Wall \
  -Wundef -Wwrite-strings -Wredundant-decls -Winline

srcdir = .
VPATH = .:./../extras
LDFLAGS =  -g
LIBS =  
CFLAGS = -g -O2 -pipe -Wall -I. # -fsanitize=address  # Adiciona a flag de instrumentação do AFL


# Change these if necessary

YACC = bison -y 
LEX = flex 
CC = /home/skid/AFLplusplus/afl-clang-fast 
CPP = /home/skid/AFLplusplus/afl-clang-fast -E

SOURCES = alias.c boa.c buffer.c cgi.c cgi_header.c config.c escape.c \
	get.c hash.c ip.c log.c mmap_cache.c pipe.c queue.c read.c \
	request.c response.c select.c signals.c util.c sublog.c

OBJS = y.tab.o lex.yy.o $(SOURCES:.c=.o) timestamp.o 

all:	boa boa_indexer

boa:	$(OBJS)
	$(AFL_CC) -o $@ $^ $(LDFLAGS) $(LIBS)   # Usa AFL_CC para compilar com AFL

boa_indexer:	index_dir.o escape.o   
	$(AFL_CC) -o $@ $^ $(LDFLAGS) $(LIBS)   # Usa AFL_CC para compilar com AFL


clean:
	rm -f $(OBJS) boa core lex.yy.c y.tab.c y.tab.h *~ boa_indexer index_dir.o   
	
distclean:	mrclean

mrclean:	clean
	rm -f config.status config.cache config.h Makefile config.log

# parser dependencies

y.tab.c y.tab.h:	boa_grammar.y
	$(YACC) -d $^

lex.yy.c:	boa_lexer.l
	$(LEX) $^

# timestamp

timestamp.o:	$(SOURCES) boa_grammar.y boa_lexer.l

# depend stuff
.depend:
	$(CPP) -MM $(SOURCES) > .depend
        
depend:
	-rm -f .depend
	$(MAKE) .depend
        
include .depend

# tags
tags:	$(SOURCES)
	ctags -o tags $^ *.h

# dist
dist:
	$(MAKE) clean
	./makedist.sh
        
# object dump
boa.objdump:    boa
	objdump --disassemble-all --source boa > $@

