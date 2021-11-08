mov &b,10 ;mov 10 into register A
@start
mov &a,&b ;mov 10 into register A
pop
jmp @start
