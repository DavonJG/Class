#CIS341 Project 2
#Author: Davon Grant

.data
	a: .word 56,3,46,47,34,12,1,5,10,8,33,25,29,31,50,43
	c: .word 0:10
	p1: .asciiz "\nUnsorted Array: \n"
	p2: .asciiz "\nSorted Array: \n"
	space: .asciiz " "
	newLine: .asciiz "\n"
	result: .word 0:100

.text

main:

	la $a0, p1
	li $v0, 4
	syscall

	la $a0, a
	addi $a1, $zero, 16
	jal printlnit


	la $a0, p2
	li $v0, 4
	syscall
	
	la $a0, a
	addi $a1, $zero, 0
	addi $a2, $zero, 15
	jal mergesort


	la $a0, a
	addi $a1, $zero, 16
	jal printlnit

	li $v0, 10
	syscall

mergesort:
	slt $t0, $a1, $a2
	beq $t0, $zero, MsExit

	addi, $sp, $sp, -16		#Creates stack space
	sw, $ra, 12($sp)
	sw, $a1, 8($sp)
	sw, $a2, 4($sp)

	add $t0, $a1, $a2		#Sets mid = low + high
	sra $t0, $t0, 1  		#Sets mid = (low+high)/2

	sw $t0, 0($sp)			#Command to store mid

	add $a2, $t0, $zero		#Command to set the argument to mid
	jal mergesort			#Initiates mergesort(a, low, mid) (a, $a1, $a2)
	
	lw $t0, 0($sp)			#Command to load mid value
	addi $s1, $t0, 1		#Solves mid+1
	move $a1, $s1			#Command to set the argument to mid
	
	lw $a2, 4($sp)			#Command to load high value into the argument

	jal mergesort			#Initiates mergesort(a, mid+1, high)

	lw, $a1, 8($sp)		
	lw, $a2, 4($sp)
	lw, $a3, 0($sp)

	jal merge

	lw $ra, 12($sp)
	addi $sp, $sp, 16		#Command to close stack

MsExit:
	jr $ra


merge:
	la	$s7, c
	add $t0, $zero, $a1 		#Sets $t0 to i
	add $t1, $zero, $a1 		#Sets $t1 to k
	addi $t2, $a3,  1 		#Sets $t2 to j
	addi $t3, $a2,  1 		#Sets $t3 to high + 1
	addi $t4, $a3,  1 		#Sets $t4 to mid + 1

while1:
	slt $t5, $t0, $t4 		#Checks if $t0 < mid+1, then $t5 ==1
	slt $t6, $t2, $t3 		#Checks if $t2 < high+1
	and $t7, $t5, $t6 		#Checks if $t5 and $t5 and $t6 are true, then $t7 is true
	beq $t7, $zero, while2 		#Checks if they are both true, then goes to while2
	
	sll $t8, $t0, 2 		#Multiplies $t0 by 4 and stores it in $t8
	add $t8, $a0, $t8 
	lw $t9, 0($t8) 			#Sets $t9 to a[i]

	sll $t8, $t2, 2 		#Multiplies $t2 by 4 stores it in $t8
	add $t8, $a0, $t8 		#Now t2 has address of a[j]
	lw $s4, 0($t8) 			#Sets $s4 to of a[j]

	sll $t5, $t1, 2 		#Multiplies k value by 4 and stores it in $t5 register
	add $t5, $s7, $t5 		#Now $t5 has the position of c[k]

					#If-statement
	slt $t7, $t9, $s4
	beq $t7, $zero, else

	sw $t9, 0($t5) 			#Stores $t9 into c[k]
	
	addi $t0, $t0, 1 		#Initiates i++
	addi $t1, $t1, 1 		#Initiates k++
	j while1

else:
	sll $t5, $t1, 2
	add $t5, $s7, $t5

	sll $t7, $t2, 2
	add $t7, $a0, $t7	
	lw $t8, 0($t7)

	sw $t8, 0($t5) 			#Stores $t8 into $t5
	
	addi $t2, $t2, 1 		#Initiates j++
	addi $t1, $t1, 1 		#Initiates k++
	j while1

while2:
	slt $t5, $t0, $t4 		#Checks if mid > i, then $t5=1
	beq $t5, $zero, while3
	
	sll $t6, $t1, 2 		#Finds c[k] and stores it in a different register
	add $t6, $s7, $t6

	sll $t7, $t0, 2
	add $t7, $a0, $t7
	lw $t8, 0($t7)

	sw $t8, 0($t6) 			#Saves $t8 to $t6
	addi $t1, $t1, 1 		#Initiates k++
	addi $t0, $t0, 1 		#Initiates i++
	j while2

while3:
	slt $t5, $t2, $t3 		#Checks if j < high +1
	beq $t5, $zero, for 		#Command to jump to for loop if it's not false

	sll $t6, $t1, 2 		#Multiplies k by 4 and stores it into $t6
	add $t6, $s7, $t6 		#$t6 takes the position of c[k]

	sll $t7, $t2, 2 		#Multiplies j by 4 and stores it into $t7
	add $t7, $a0, $t7 		#$t7 takes the position of a[j]	
	lw $t8, 0($t7) 			#$t8 now is set to the position of a[j]
	
	sw $t8, 0($t6) 			#Saves the value of $t8 into $t6 (c[k])
	
	addi $t1, $t1, 1 		#Initiates k++
	addi $t2, $t2, 2 		#Initiates j++

	j while3

for:
	slt $t5, $a1, $t1
	beq $t5, $zero, exit

	sll $t6, $a1, 2 		#Value of c[i]
	add $t6, $s7, $t6
	lw  $t7, 0($t6)

	sll $t8, $a1, 2 		#Address of a[i]
	add $t8, $a0, $t8

	sw $t7, 0($t8) 			#Saves the value of c[i] into a[i]
	addi $a1, $a1, 1
	j for
	
printlnit:
	addi $t0, $zero, 0
	addi $s7, $a0, 0
	la $t2, space

printarray:
	slt $t1, $t0, $a1
	beq $t1, $zero, exit

	addi $v0, $zero, 1
	lw $a0, 0($s7)
	syscall

	add $a0, $t2, $zero
	addi $v0, $zero, 4
	syscall
	
	addi $s7, $s7, 4
	addi $t0, $t0, 1
	j printarray
	
exit:
	jr $ra

