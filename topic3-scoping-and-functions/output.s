.data
var_x: .word 0
.text
.globl main

addTwoNumbers:
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $fp, 4($sp)
	move $fp, $sp

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	move $t0, $a0
	move $t1, $a1
	add $t2, $t0, $t1
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

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	li $t1, 0
	sw $t1, -12($fp)
	li $t1, 2
	sw $t1, var_x
	li $t3, 4
	sw $t3, var_x
	li $a0, 1
	li $a1, 2
	jal addTwoNumbers

	move $t4, $v0
	sw $t4, var_x
	lw $t9, var_x
	move $a0, $t9
	li $v0, 1
	syscall

	lw $v0, -12($fp)

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $t1, 1
	sw $t1, var_x
	li $v0, 10
	syscall
