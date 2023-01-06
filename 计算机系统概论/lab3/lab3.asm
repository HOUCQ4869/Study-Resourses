.ORIG x3000
LDI R0, NUM
LD R1, DATA

        ADD R2, R2, #1
        ADD R7, R7, #1
        ;初始化R2, R7计数为1
AGAIN   ADD R0, R0, #-1
        BRz OVER
        LDR R3, R1, #0
        LDR R4, R1, #1
        ADD R1, R1, #1
        ;得到相邻的字符，并将指针向后推移一位
        NOT R5, R3
        ADD R5, R5 #1
        ADD R6, R5, R4
        ;减法计算是否相等，则跳转到COUNT
        BRz COUNT
        AND R7, R7, #0
        ADD R7, R7, #1
        ;重新赋值计数
        BRnzp AGAIN
        
        
COUNT   ADD R7, R7, #1
        NOT R3, R2
        ADD R3, R3, #1
        ADD R4, R7, R3
        BRnz AGAIN
        ;比较此时相等长度与最大长度R2的大小
        ADD R2, R7 #0
        BRnzp AGAIN
        

OVER    STI R2, RESULT
        HALT

RESULT .FILL x3050
NUM .FILL x3100
DATA .FILL x3101

.END