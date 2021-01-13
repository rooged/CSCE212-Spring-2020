.data
	s: .asciiz "Hello, World!"
	newline: .asciiz "\n"

.text
	li $v0, 4		#print string
	la $a0, s		#loading the address of s into a0
	syscall
	li $v0, 4
	la $a0, newline
	syscall