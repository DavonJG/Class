#Hello World Program

.data #Data Declaration Section
out_string: .asciiz "\nHello, World!\n"

.text #Text section | Assembly Language Instructions

main:

li $v0, 4					#System call code for printing string=4

la $a0, out_string			# load address of string to be printed into $a0

syscall						# call the OS to perform operatoins specified in $v0

li $v0, 10					# terminate the program

syscall