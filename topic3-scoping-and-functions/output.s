.data
var_x: .word 0
.text
.globl main
main:
	li $t1, 2
	sw $t1, var_x
	li $t9, 2
	li $t8, 3
	add $t0, $t9, $t8
	sw $t0, var_x
	lw $t9, var_x
	move $a0, $t9
	li $v0, 1
	syscall
	li $v0, 10
	syscall
