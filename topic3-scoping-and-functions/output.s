.data
var_arg: .word 0
.text
.globl main

addSomeNums:
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

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	addi $sp, $sp, -4
	sw $zero, 0($sp)

	li $t1, 2
	sw $t1, -12($fp)
	li $t1, 3
	sw $t1, -16($fp)
	li $t3, 5
	sw $t3, -20($fp)
	lw $a0, -20($fp)
	li $v0, 1
	syscall
	li $t1, 4
	sw $t1, -12($fp)
	li $t1, 8
	sw $t1, -16($fp)
	li $t4, 32
	sw $t4, -20($fp)
	lw $a0, -20($fp)
	li $v0, 1
	syscall
	li $t1, 20
	sw $t1, -12($fp)
	li $t1, 10
	sw $t1, -16($fp)
	li $t5, 2
	sw $t5, -20($fp)
	lw $a0, -20($fp)
	li $v0, 1
	syscall
	li $t1, 5
	sw $t1, -12($fp)
	li $t1, 10
	sw $t1, -16($fp)
	li $a0, 5
	li $a1, 10
	jal addSomeNums

	move $t6, $v0
	sw $t6, -20($fp)
	lw $a0, -20($fp)
	li $v0, 1
	syscall

	li $v0, 0

	lw $ra, 8($fp)
	lw $fp, 4($fp)
	addi $sp, $sp, 12
	jr $ra
	li $t1, 1
	sw $t1, var_arg
	li $v0, 10
	syscall
