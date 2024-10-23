.data
var_x: .word 0
var_y: .word 0
var_z: .word 0
.text
.globl main
main:
	li $t1, 10
	sw $t1, var_x
	li $t1, 5
	sw $t1, var_y
	li $t2, 5
	sw $t2, var_z
	lw $t9, var_z
	move $a0, $t9
	li $v0, 1
	syscall
	li $t1, 6
	sw $t1, var_x
	li $t1, 7
	sw $t1, var_y
	li $t3, 42
	sw $t3, var_z
	lw $t9, var_z
	move $a0, $t9
	li $v0, 1
	syscall
	li $t1, 20
	sw $t1, var_x
	li $t1, 4
	sw $t1, var_y
	li $t4, 5
	sw $t4, var_z
	lw $t9, var_z
	move $a0, $t9
	li $v0, 1
	syscall
	li $v0, 10
	syscall
