.data
var_x: .word 0
var_result: .word 0
.text
.globl main
main:
	add $t0, $t0, $t1
	sw $t2, var_result
	li $v0, 10
	syscall
