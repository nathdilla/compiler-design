.data
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

	# assignment of a
	li $t1, 2
	# store value of a
	sw $t1, -12($fp)
	lw $t9, -12($fp)
	li $t8, 1
	add $t0, $t9, $t8
	# assignment of a
	# store value of a
	sw $t0, -12($fp)
	# write a
	lw $a0, -12($fp)
	li $v0, 1
	syscall

	# return 0
	li $v0, 0

	# restore return address
	lw $ra, 8($fp)
	# restore frame pointer
	lw $fp, 4($fp)
	# deallocate stack space
	addi $sp, $sp, 12
	jr $ra
# Exit program
	li $v0, 10
	syscall
