li $t0, 0x80000021
sll $t0, $t0, 1
srl $t0, $t0, 2
sll $t0, $t0, 1
addi $t1, $zero, 16
beq $t0, $t1, Else
andi $t2, $t0, 1
j Done
Else: ori $t2, $t0, 1
Done:...