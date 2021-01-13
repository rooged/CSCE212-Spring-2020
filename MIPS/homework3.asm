#bubble sort least to heighest
.data
	array: .space 20
	s: .asciiz "Enter a number: "
	done: .asciiz "Done!\n"
	list: .asciiz "Sorted list: "
	space: .asciiz " "

.text
	la $a1, array	#load array address
	li $s0, 0		#initialize enter counter	
	
enter:
	li $v0, 4		#print string
	la $a0, s		#loading the address of s into a0
	syscall		#system call
	li $v0, 5		#enter integer
	syscall
	move $t0, $v0	#moves entered value to $t0
	sw $t0, array($s0)	#stores $t0 into array[i], i = $s0
	addi $s0, $s0, 4	#shifts to next $s0 to next array element
	beq $s0, 20, bubble	#branches when array is filled
	j enter		#jumps back to start
	
bubble:
	li $t7, 24	#initialize end variables
	li $t1, 8		#initialize i + 1
loop1:			#outer loop
	lw $t0, array($0)	#loads array into $t0
	sub $t4, $t7, $t1	#subtracts $t7 - $t1
	li $t2, 0		#initializes $t2
loop2:			#inner loop
	addi $t3, $t2, 4	#adds 4 to $t2 to get array[i+1]
	lw $t6, array($t3)	#loads array[$t3] into $t6
	blt $t0, $t6, swap	#branches if $t0 < $t6, if so goes to swap
	sw $t6, array($t2)	#stores $t6 into array[$t2]
	j endLoop		#jump to end loop condition
swap:
	sw $t0, array($t2)	#stores $t0 into array[$t2]
	lw $t0, array($t3)	#loads array[$t3] into $t0
endLoop:
	addi $t2, $t2, 4	#adds to next array element
	blt $t2, $t4, loop2	#branches if $t2 < $t4, goes to loop2
	sw $t0, array($t4)	#stores $t0 into array[$t4]
	addi $t1, $t1, 4	#adds to next array element
	blt $t1, $t7, loop1	#branches if $t1 < $t7, goes to loop1
	
print:
	li $v0, 4
	la $a0, done
	syscall
	li $v0, 4
	la $a0, list
	syscall
	li $t1, 0		#initializes $t1
printLoop:		#loop to print array elements
	lw $t0, array($t1)	#loads array[$t1] into $t0
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, space
	syscall
	addi $t1, $t1, 4	#adds to get next array element
	beq $t1, 20, exit	#branches if $t1 == 20, if so jumps to exit
	j printLoop	#jumps back to beginning

exit:
	#exits
	li $v0, 10
	syscall
