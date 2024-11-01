.data
var_arg: .word 0
.text
.globl main

addTwoNums:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# allocate memory for result
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for a
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for b
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	move $t0, $a0
	move $t1, $a1
	add $t2, $t0, $t1
	# assignment of result
	# store value of result
	sw $t2, -12($fp)

	lw $v0, -12($fp)

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra

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

	li $t1, 2
	# store value in array arr
	sw $t1, -32($sp)
	# array access of arr
	lw $t3, -32($sp)
	# assignment of x
	# store value of x
	sw $t3, -12($fp)
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
