.data
var_x: .word 0
var_y: .word 0
.text
.globl main
main:
	li $t1, 1
	sw $t1, var_x
	li $t1, 8
	li $t9, 1
	add $t0, $t9, $t1
	sw $t2, var_y
	li $t3, 6
	sw $t3, var_x
	li $t1, 6
	sw $t1, var_x
	li $t4, 8
	sw $t4, var_x
	li $t1, 1
	sw $t1, var_y
	li $t6, 3
	sw $t6, var_y
	lw $t9, var_x
	move $a0, $t9
	li $v0, 1
	syscall
	lw $t9, var_y
	move $a0, $t9
	li $v0, 1
	syscall
	li $v0, 10
	syscall
