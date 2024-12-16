.data
var_globalCounter: .word 0
.text
.globl main

main:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# allocate memory for result
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# allocate memory for intCounter
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	# assignment of globalCounter
	li $t1, 10
	# store value of globalCounter
	sw $t1, var_globalCounter
	jal modLoop

	move $t0, $v0

	# return 0
	li $v0, 0
	j main_END


main_END:
	# restore return address
	lw $ra, 8($fp)
	# restore frame pointer
	lw $fp, 4($fp)
	# deallocate stack space
	addi $sp, $sp, 12
	jr $ra

processInt:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# allocate memory for num
	addi $sp, $sp, -4
	sw $zero, 0($sp)

	move $t1, $a0
# IF STMT START
if_label_1896863326232863709:
	li $t8, 1
	seq $t2, $t1, $t8
	beq $t2, $zero, if_label_1899926484203392607
# IF BLOCK START
if_label_1902989642173921505:

	# return 10
	li $v0, 10
	j processInt_END
	j if_label_1898394905218128158
# IF STMT START
if_label_1899926484203392607:
	li $t8, 3
	slt $t3, $t1, $t8
	beq $t3, $zero, if_label_1904521221159185954
# IF BLOCK START
if_label_1907584379129714852:

	# return 20
	li $v0, 20
	j processInt_END
	j if_label_1898394905218128158
# IF STMT START
if_label_1904521221159185954:
	li $t8, 3
	slt $t4, $t8, $t1
	beq $t4, $zero, if_label_1909115958114979301
# IF BLOCK START
if_label_1912179116085508199:

	# return 30
	li $v0, 30
	j processInt_END
	j if_label_1898394905218128158
# IF BLOCK START
if_label_1909115958114979301:

	# return 40
	li $v0, 40
	j processInt_END
	j if_label_1898394905218128158
# IF STMT END
if_label_1898394905218128158:


processInt_END:
	# restore return address
	lw $ra, 8($fp)
	# restore frame pointer
	lw $fp, 4($fp)
	# deallocate stack space
	addi $sp, $sp, 12
	jr $ra

modLoop:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	# assignment of globalCounter
	li $t1, 1
	# store value of globalCounter
	sw $t1, var_globalCounter
# WHILE STMT START
if_label_53247815434552:
	lw $t9, var_globalCounter
	li $t8, 20
	slt $t0, $t9, $t8
	seq $t1, $t9, $t8
	or $t5, $t0, $t1
	beq $t5, $zero, if_label_53290433877529
# IF BLOCK START
if_label_53333052320506:
# IF STMT START
if_label_53418289206460:
	lw $t9, var_globalCounter
	li $t8, 2
	div $t9, $t8
	mfhi $t6
	li $t8, 0
	seq $t7, $t6, $t8
	beq $t7, $zero, if_label_53460907649437
# IF BLOCK START
if_label_53588762978368:
	# write globalCounter
	lw $t9, var_globalCounter
	move $a0, $t9
	li $v0, 1
	syscall
	j if_label_53460907649437
# IF STMT END
if_label_53460907649437:
	lw $t9, var_globalCounter
	li $t8, 1
	add $t8, $t9, $t8
	# assignment of globalCounter
	# store value of globalCounter
	sw $t8, var_globalCounter
# IF STMT START
if_label_53631381421345:
	lw $t9, var_globalCounter
	li $t8, 16
	seq $t9, $t9, $t8
	beq $t9, $zero, if_label_53673999864322
# IF BLOCK START
if_label_53801855193253:
# BREAK STMT
j if_label_53290433877529
	j if_label_53673999864322
# IF STMT END
if_label_53673999864322:
	j if_label_53247815434552
# IF STMT END
if_label_53290433877529:


modLoop_END:
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
