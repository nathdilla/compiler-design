all: parser

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h AST.c symbol_table.c semantic.c optimizer.c code_generator.c
	gcc -o parser parser.tab.c lex.yy.c AST.c symbol_table.c semantic.c optimizer.c code_generator.c
	./parser testProg.cmm

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output lex.yy.o parser.tab.o AST.o symbol_table.o semantic.o code_generator.o optimizer.o TAC.ir optimized_TAC.ir output.s
	ls -l
