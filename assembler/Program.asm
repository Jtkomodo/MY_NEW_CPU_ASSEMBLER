@start n
mov &A,0x200 ;helllo
sub 50
mov [0x16],32
rd [0x16]
je @loop
mov [0x16],54

@loop
sub 300
jump @start
