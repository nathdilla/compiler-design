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

	li $t0, 7
	# assignment of x
	# store value of x
	sw $t0, -12($fp)

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $v0, 10
	syscall
