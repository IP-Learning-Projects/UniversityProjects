add $0, $0, $0
lw $2, 0x40($0) # INW0=4
lw $3, 0x44($0) # INW1=2
add $4, $2, $2 #2*a
add $5, $4, $2 #3*a=12
add $6, $3, $3 # 2*b=4
sub $7, $5, $6 #3*a-2*b
sw $2, 0x48($0)
sw $3, 0x48($0)
sw $7, 0x48($0)