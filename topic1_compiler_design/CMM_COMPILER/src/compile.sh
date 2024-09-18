echo "Running compile script.."
set -x
flex lexer.l
gcc lex.yy.c -o lexer
./lexer testProg.cmm
