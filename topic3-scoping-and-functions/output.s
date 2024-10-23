.data
var_x: .word 0
var_result: .word 0
.text
.globl main
main:

add:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp
	add $t0, $t0, $t1
	sw $t2, var_result
	sw $t4, var_x
	lw $t9, var_x
	move $a0, $t9
	li $v0, 1
	syscall
	li $v0, 10
	syscall
