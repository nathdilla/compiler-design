.data
var_arg: .word 0
.text
.globl main

main:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# allocate memory for x
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for arr
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for array arr
	addi $sp, $sp, -20

	# assignment of x
	li $t1, 1
	# store value of x
	sw $t1, -12($fp)
	li $t1, 4
	# store value in array arr
	sw $t1, -20($sp)
	li $t1, 4
	# store value in array arr
	sw $t1, -24($sp)
	li $t1, 7
	# store value in array arr
	sw $t1, -28($sp)
	li $t1, 4
	# store value in array arr
	sw $t1, -32($sp)
	li $t1, 1
	# store value in array arr
	sw $t1, -36($sp)
	# array access of arr
	lw $t0, -28($sp)
	# assignment of x
	# store value of x
	sw $t0, -12($fp)
	# write x
	lw $a0, -12($fp)
	li $v0, 1
	syscall

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	# assignment of arg
	li $t1, 1
	# store value of arg
	sw $t1, var_arg
	li $v0, 10
	syscall
