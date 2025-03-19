#CIS341 Project 1
#Author: Davon Grant

.data

array1: .word 1,4,7,10,25,3,15,13,17,21
array2: .word 0:10
comma: .asciiz ", "

.text

main:
	la $a0, array1
	li $a1, 0	# $t0 = low
	li $a2, 4	# $t1 = mid 
	li $a3, 9	# $t2 = high
	
	jal merge
	j print
	
print:
	li $t9, 9
	li $t8, 0
	jal printloop
	
	printloop:
	bgt $t8, $t9, exit	# branch to exit if x > 10 
	la $t3, array2
	add $t4, $t8, $zero
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t6, 0($t5)		# $t6 = a[x]
	
	li $v0, 1
	move $a0, $t6		# moves value to $a0 to be printed 
	syscall 
	
	li $v0, 4
	la $a0, comma
	syscall
	
	addi $t8, $t8, 1	# $t8++
	j printloop			# repeats print

merge:
	add $s0, $a1, $zero	# $s0 = i = low
	addi $s1, $a2, 1	# $s1 = j = mid+1
	add $s2, $a1, $zero	# $s2 = k = low
	
loop1:
	bgt $s0, $a2, loop2	# i <= mid &
	bgt $s1, $a3, loop2	# & j <= high  else got to loop2
	
	la $t3, array1
	add $t4, $s0, $zero
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t6, 0($t5)		# $t6 = a[i]

	add $t4, $s1, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t7, 0($t5)		# $t7 = a[j]
	
	la $t3, array2
	add $t4, $s2, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $s4, $t4, $t3	# $s4 = c[k]

	bge $t6, $t7, else	# a[i] < a[j] otherwise, do else

	sw $t6, 0($s4)		# c[k] = a[i]
	addi $s2, $s2, 1	# k++
	addi $s0, $s0, 1	# i++
	
	j loop1			# repeat loop

	else:
		sw $t7, 0($s4)		# c[k] = a[j]
		addi $s2, $s2, 1	# k++
		addi $s1, $s1, 1	# j++
		
		j loop1			# repeat loop1
	
loop2:
	bgt $s0, $a2, loop3	# i <= mid else go to loop3
	
	la $t3, array1		
	add $t4, $s0, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t6, 0($t5)		# $t6 = a[i]

	la $t3, array2
	add $t4, $s2, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $s4, $t4, $t3	# $s4 = c[k]

	sw $t6, 0($s4)		# c[k] = a[i]
	addi $s3, $s3, 1	# k++
	addi $s0, $s0, 1	# i++

	j loop2			# repeat loop2

loop3:
	bgt $s1, $a3, for	# j <= high else go to for
	
	la $t3, array2
	add $t4, $s1, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t7, 0($t5)		# $t6 = a[j]

	la $t3, array1
	add $t4, $s2, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4	# 4*$t4
	add $s4, $t4, $t3	# $t8 = c[k]

	sw $t7, 0($s4)
	addi $s3, $s3, 1	# k++
	addi $s0, $s0, 1	# i++
	
	j loop3

for:
	bge $s0, $a2, exitmerge	# i < mid else got to exitmerge
	
	la $t3, array2
	add $t4, $s0, $zero
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $t5, $t4, $t3
	lw $t7, 0($t5)		# $t7 = c[i]

	la $t3, array1
	add $t4, $s0, $zero 
	add $t4, $t4, $t4
	add $t4, $t4, $t4
	add $s4, $t4, $t3	# s4 = a[i]
		
	sw $t7, 0($s4) 		# a[i] = c[i]
		
	addi $s0, $s0, 1	# i++
	
	j for

exitmerge:
	jr $ra

exit:	
	li $v0, 10 
	syscall
