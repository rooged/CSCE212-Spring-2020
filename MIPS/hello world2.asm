.data
	s: .asciiz "Hello, World!\n"
	newline: .asciiz "\n"

.text
	li $v0, 4		#print string
	la $a0, s		#loading the address of s into a0
	syscall
	li $s0, 0

loop:
	slti $t0, $s0, 10
	beq $t0, $zero, exit
	
	li $v0, 1
	move $a0, $s0
	syscall
	
	addi $s0, $s0, 1
	
	j loop
	
exit:
	li $v0, 10
	syscall
