.data
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

	# allocate memory for y
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for hello
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for z
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for array hello
	addi $sp, $sp, -20

	# assignment of x
	li $t1, 4
	# store value of x
	sw $t1, -12($fp)
	# assignment of y
	li $t1, TRUE
	# store value of y
	sw $t1, -16($fp)
	# assignment of z
	li $t1, 2.000000
	# store value of z
	sw $t1, -24($fp)

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $v0, 10
	syscall
