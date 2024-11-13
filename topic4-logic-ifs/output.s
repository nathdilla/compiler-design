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

	# allocate memory for b
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	li $t0, 3
	# assignment of a
	# store value of a
	sw $t0, -12($fp)
	li $t9, 0x40266666
	mtc1 $t9, $f1
	# assignment of b
	# store value of b
	s.s $f1, -16($fp)
	# write b
	l.s $f12, -16($fp)
	li $v0, 2
	syscall

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $v0, 10
	syscall
