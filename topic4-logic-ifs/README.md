C Minus Minus Compiler by Nathan Dilla

github: https://github.com/nathdilla/compiler-design/tree/if-statements
LOOM: https://www.loom.com/share/cb4f5951e38d4dc088f26ae5f9d20b53
LOOM P2: https://www.loom.com/share/2ca197f5dfb74732ae2b05bb552448d7

Table of Contents

	1.	Introduction
	2.	Features
	3.	Installation
	4.	Usage
	5.	Architecture Overview
	•	1. Lexical Analysis
	•	2. Parsing and AST Construction
	•	3. Semantic Analysis
	•	4. Code Generation
	•	5. Code Optimization
	6.	Testing
	7.	Known Issues
	8.	Future Work
	9.	Contributors

Introduction

The C– Compiler is a lightweight compiler built using Flex and Bison. It compiles programs written in the C– programming language, a simplified subset of C. The compiler processes input code through various stages, including lexical analysis, parsing, AST construction, semantic analysis, code generation, and code optimization, ultimately producing executable machine code.

Features

	•	Lexical Analysis: Tokenizes source code into meaningful symbols.
	•	AST Construction: Builds an Abstract Syntax Tree to represent the program’s structure.
	•	Semantic Analysis: Ensures the code follows type rules, variable declarations, and other semantic constraints.
	•	Code Generation: Produces intermediate code in Three Address Code (TAC) or assembly.
	•	Code Optimization: Optimizes the generated code for better performance and reduced size.

Installation

Prerequisites

	•	Flex (Fast Lexical Analyzer)
	•	Bison (Parser Generator)
	•	GCC or any compatible C compiler
	•	SPIM (for MIPS assembly testing)

Steps

	1.	Clone the repository:

git clone https://github.com/nathdilla/compiler-design/tree/if-statements
cd topic4-logic-ifs


	2.	Build the compiler:

make clean; make parser


	3.	Ensure the required tools are installed:

sudo apt-get install flex bison gcc

Usage

Compile a Program

Run the compiler on a C– source file:

./cmm_compiler input.cmm

Output Files

	•	AST Tree Visualization: ast_output.txt
	•	Generated Code: output.s (MIPS assembly)
	•	Optimization Logs: optimizer_log.txt

Architecture Overview

1. Lexical Analysis

	•	Tool: Flex
	•	Description: Scans the input source code and generates tokens (e.g., identifiers, keywords, symbols).
	•	Files:
	•	lexer.l: Contains token definitions and regular expressions.

2. Parsing and AST Construction

	•	Tool: Bison
	•	Description: Builds the grammar rules and constructs the Abstract Syntax Tree (AST).
	•	Files:
	•	parser.y: Contains grammar rules and AST node definitions.
	•	AST.h / AST.c: Defines the structure and traversal of the AST.

3. Semantic Analysis

	•	Description: Checks for:
	•	Type correctness (e.g., type mismatches in assignments).
	•	Variable declaration and usage.
	•	Scope resolution using a Symbol Table.
    •	Generates TAC (Three Address Code)
	•	Files:
	•	semantic.c: Implements semantic rules and validations.
	•	symbol_table.h / symbol_table.c: Manages scopes and variable tracking.
    •	TAC.ir: TAC file location.

4. Code Generation

	•	Description: Converts the AST into:
	•	MIPS Assembly Code: Final output for execution.
	•	Files:
	•	code_generator.c: Generates TAC and converts it to MIPS assembly.
	•	output.s: Final assembly output.

5. Code Optimization

	•	Description:
	•	Implements techniques like constant folding, dead code elimination, and constant propagation
	•	Optimizes intermediate TAC before generating assembly.
	•	Files:
	•	code_optimizer.c: Core optimization logic.
	•	optimizedTAC.ir: Logs optimization steps for debugging.

Testing

Sample Programs

	1.	adaptedTest.cmm - Adapted test code given be Artzi. Does NOT execute.
	2.	testProg2.cmm - Demonstrates while loops, if statements, function calls/declarations and arithmetic operations

Run Tests

Change the input file accordingly in parser.y

Known Issues

	•	Optimization features are turned off because they break the code
    •	Logical comparisons break when using variables or different types other than int.
    •	Type cast parsing is broken for one of the operands.
    •	No Chars
    •	No type checking for function returns
    •	Parenthesis operations do not work
    •	No evaluating expressions as parameters
    

Contributors

	•	Nathan Dilla 
    •	eli streitmatter
