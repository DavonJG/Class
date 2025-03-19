	.data 
Prompt1: 	.asciiz 	"\nPlease type in an integer:\n"
Result_MSG: 	.asciiz 	"\nThe answer is:\n"

	.text
main:	

	## Get the integer number from user, put into $t0.
	la $a0, Prompt1
        li $v0, 4
        syscall

	li $v0, 5 		# load syscall read_int into $v0.
	syscall 		# make the syscall.
	move $t0, $v0 		# move the number read into $t0.

	## Put the user input into the arguement, $a0, and call Fib
	add	$a0, $zero, $t0
	jal	Fib

	## Retrieve the return value
	add	$t0, $zero, $v0

	## Print out result.
	la 	$a0, Result_MSG
        li 	$v0, 4
        syscall

	add 	$a0, $zero, $t0 		
	li 	$v0, 1 		
	syscall	
	
	## Code for syscall: exit
	li	$v0,10		
	syscall

Fib:
	addi	$sp, $sp, -12			# Allocate memory for saving register values.
	sw	$ra, 8($sp)			# Save return address.
	sw	$a0, 4($sp)			# Save argument n.
	sw	$s0, 0($sp)			# Save $s0, which will hold Fib(n-1)

	bne	$a0, $zero, L1			# Check if n == 0, if not goto L1			
	add	$v0, $zero, $zero		# n == 0, return 0
	j	Exit				# Jump to Exit to clean up stack

L1:			
	addi	$t0, $zero, 1			# Check if n == 1, if not goto L2
	bne	$a0, $t0, L2			# n == 1, return 1
	addi	$v0, $zero, 1			
	j	Exit				# Jump to Exit to clean up stack

L2:
	addi	$a0, $a0, -1			# n = n - 1
	jal	Fib				# Calculate Fib(n-1)
	
	add	$s0, $zero, $v0			# $s0 = Fib(n-1)

	addi	$a0, $a0, -1			# n = n - 1 - 1 = n - 2
	jal	Fib				# Calculate Fib(n-2)

	add	$v0, $s0, $v0			# $v0 = Fib(n-1) + Fib(n-2)

Exit:	lw	$s0, 0($sp)			# Restore $s0
	lw	$a0, 4($sp)			# Restore argument n.
	lw	$ra, 8($sp)			# Restore return address.
	addi	$sp, $sp, 12			# Free the memory.
	

	jr	$ra				# return