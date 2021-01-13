.data
	s: .asciiz "Enter 2 numbers:"
	newline: .asciiz "\n"
	number1: .asciiz "First number: "
	number2: .asciiz "Second number: "
	andOp: .asciiz "Bitwise AND: "
	orOp: .asciiz "Bitwise OR: "
	exOrOp: .asciiz "Bitwise XOR: "
	firstOp: .asciiz "For 1st then 2nd, the <<, >>, and ~: "
	secondOp: .asciiz "For 2nd then 1st, the <<, >>, and ~: "

.text
	#prints out string
	li $v0, 4		#print string
	la $a0, s		#loading the address of s into a0
	syscall		#system call
	li $v0, 4
	la $a0, newline
	syscall
	
	#takes in first int
	li $v0, 5		#take in integer
	syscall
	move $s0, $v0	#move value from v0 to s0
	
	#takes in second int
	li $v0, 5
	syscall
	move $s1, $v0	#move value from v0 to s1

	#prints out first number
	li $v0, 4
	la $a0, number1	
	syscall
	li $v0, 1		#print integer
	move $a0, $s0
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#prints out second number
	li $v0, 4
	la $a0, number2
	syscall
	li $v0, 1
	move $a0, $s1
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#and operation
	li $v0, 4
	la $a0, andOp	
	syscall
	and $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#or operation
	li $v0, 4
	la $a0, orOp	
	syscall
	or $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#exclusive or operation
	li $v0, 4
	la $a0, exOrOp	
	syscall
	xor $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#shift left, shift right, and not operation of 1st number
	li $v0, 4
	la $a0, firstOp	
	syscall
	sllv $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	srlv $s3, $s0, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	not $s3, $s0
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#shift left, shift right, and not operation of 2nd number
	li $v0, 4
	la $a0, secondOp	
	syscall
	sllv $s3, $s1, $s0
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	srlv $s3, $s1, $s0
	li $v0, 1
	move $a0, $s3
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	li $t0, -1
	not $s3, $s1
	li $v0, 1
	move $a0, $s3
	syscall
	
	#exit
	li $v0, 10
	syscall