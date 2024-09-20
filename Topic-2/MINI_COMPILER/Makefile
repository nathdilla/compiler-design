all: parser

mini_parser1.tab.c mini_parser1.tab.h:	mini_parser1.y
	bison -t -v -d mini_parser1.y

lex.yy.c: lexer.l mini_parser1.tab.h
	flex lexer.l

parser: lex.yy.c mini_parser1.tab.c mini_parser1.tab.h AST1.c AST1.h
	cc -o parser mini_parser1.tab.c lex.yy.c AST1.c
	./parser testProg.cmm

clean:
	rm -f parser mini_parser1.tab.c lex.yy.c mini_parser1.tab.h mini_parser1.output lex.yy.o mini_parser1.tab.o AST1.o
	ls -l
