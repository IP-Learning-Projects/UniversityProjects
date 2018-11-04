rep: lw $2, 0x40($0)
	lw $3, 0x44($0)
	sub $4, $2, $3
	beq $3, $2, display
	add $4, $2, $3
display: sw $4 ,0x48($0)
	beq $0, $0, rep