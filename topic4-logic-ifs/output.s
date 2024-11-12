.data
var_one: .word 0
var_two: .word 0
var_three: .word 0
.text
.globl main

main:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# allocate memory for a
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for b
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for c
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# assignment of a
	li $t1, 1
	# store value of a
	sw $t1, -12($fp)
	# assignment of b
	li $t1, 2.300000
	# store value of b
	sw $t1, -16($fp)
	# assignment of c
	li $t1, TRUE
	# store value of c
	sw $t1, -20($fp)

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $v0, 10
	syscall
