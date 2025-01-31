# Simple Assembly
An incomplete assembly language for Raspberry-Pi 3b.  
Takes in a text file of assembly commands such as:
```
MOVW RD, 0
MOVT RD, 0
MOVW R4, 0
MOVT R4, 3F20
ADD R2, R4, 08
LDR R3, (R2)
ORR R3, R3, 008
STR R3, (R2)
ADD R3, R4, 1c >>start
MOVW R2, 0000
MOVT R2, 0020
STR R2, (R3)
STMEA RD!
MOVW R0, 0900
MOVT R0, 003D
STREA R0, (RD!), 4
BL <<delay
LDMEA RD!
ADD R3, R4, 28
MOVW R2, 0000
MOVT R2, 0020
STR R2, (R3)
STMEA RD!
MOVW R0, 4240
MOVT R0, 000F
STREA R0, (RD!), 4
BL <<delay
LDMEA RD!
B <<start
LDREA R6, (RD!), 4 >>delay
SUBS R6, R6, 01 >>sub
BPL <<sub
BX RE
```
Returns a kernel7.img file to run on the device.
