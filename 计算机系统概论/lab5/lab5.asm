 .ORIG x800
        ; (1) Initialize interrupt vector table.
        LD R0, VEC
        LD R1, ISR
        STR R1, R0, #0

        ; (2) Set bit 14 of KBSR.
        LDI R0, KBSR
        LD R1, MASK
        NOT R1, R1
        AND R0, R0, R1
        NOT R1, R1
        ADD R0, R0, R1
        STI R0, KBSR

        ; (3) Set up system stack to enter user space.
        LD R0, PSR
        ADD R6, R6, #-1
        STR R0, R6, #0
        LD R0, PC
        ADD R6, R6, #-1
        STR R0, R6, #0
        ; Enter user space.
        RTI
        
VEC     .FILL x0180
ISR     .FILL x1000
KBSR    .FILL xFE00
MASK    .FILL x4000
PSR     .FILL x8002
PC      .FILL x3000
        .END

        .ORIG x3000
        ; *** Begin user program code here ***
PRIN    LEA R0, NUM
        TRAP x22        ;"PB21111618 "
        JSR DELAY
        LDI R0, N
        ADD R0, R0, #1
        BRz PRIN        ;根据N判断是否循环输出
        BRnzp HONOI
        
DELAY   ST R1, SAVERR1  ;延迟便于显示
        LEA R1, COUNT
REP     ADD R1, R1, #-1
        BRp REP
        LD R1, SAVERR1
        RET
        
HONOI   LDI R1, N       ;HONOI子例程解决问题
        ADD R3, R1, #0  
        ADD R1, R1, #1
        JSR SKIP
        BRnzp DONE
        
SKIP    ADD R1, R1, #-1
        BRz ZERO
        JSR SKIP
        ADD R2, R2, R2
        ADD R2, R2, #1
        ADD R3, R3, #-1 ;根据R3即N的值记录跳出次数
        BRz DONE
        RET
        
ZERO    AND R2, R2, #0  ;减至0时则开始跳出递归
        RET
        
DONE    LD R4, HUNDRED
        LD R5, TEN
        ADD R3, R2, #0  ;R3表示计算结果
        
        AND R1, R1, #0
HUND    ADD R1, R1, #1
        ADD R3, R3, R4 
        BRzp HUND
        ADD R1, R1, #-1 ;循环减100得到百位数
        
        NOT R4, R4
        ADD R4, R4, #1
        ADD R3, R3, R4  ;恢复到减完百位
        
        AND R2, R2, #0
TENC    ADD R2, R2, #1
        ADD R3, R3, R5 
        BRzp TENC
        ADD R2, R2, #-1 ;循环减10得到十位数
        ADD R3, R3, #10 ;恢复到个位数R3
        
        LEA R0, RESUL
        TRAP x22    ;“Tower of honoi needs ”
        
        ADD R6, R1, #0  ;输出百位
        BRz TENP
        JSR APPE
        
TENP    ADD R6, R2, #0  ;输出十位
        BRz BITP
        JSR APPE
            
BITP    ADD R6, R3, #0  ;输出个位
        JSR APPE
        BRnzp OVERD
        
APPE    ADD R0, R6, #15
        ADD R0, R0, #15
        ADD R0, R0, #15
        ADD R0, R0, #3  ;转化为ASCLL码输出
        TRAP x21
        RET
        
OVERD   LEA R0, RESULT
        TRAP x22    ;“ moves.”
        HALT
        
HUNDRED .FILL #-100
TEN .FILL #-10
        
SAVERR1 .FILL x0000
COUNT .FILL #2500
NUM .STRINGZ "PB21111618 "
RESUL .STRINGZ "Tower of honoi needs "
RESULT .STRINGZ " moves."
N .FILL x3FFF
        ; *** End user program code here ***
        .END

        .ORIG x3FFF
        ; *** Begin honoi data here ***
HONOI_N .FILL xFFFF
        ; *** End honoi data here ***
        .END

        .ORIG x1000
        ; *** Begin interrupt service routine code here ***
        ST R0, SAVER0
        ST R1, SAVER1
        ST R2, SAVER2
        TRAP x20
        ADD R2, R0, #0
        AND R0, R0, #0
        ADD R0, R0, x000A
        TRAP x21    ;显示换行
        ADD R0, R2, #0
        TRAP x21    ;显示N

        ADD R1, R0, #-15
        ADD R1, R1, #-15
        ADD R1, R1, #-15
        ADD R1, R1, #-3 ;根据ASCLL码判断是否为十进制数
        BRn NONUM
        ADD R1, R1, #-10
        BRzp NONUM
        BRnzp YESNUM
        
YESNUM  LEA R0, YESD
        TRAP x22    ;" is a decimal digit."
        ADD R1, R1, #10
        STI R1, HN  ;当N有效时更改N的值
        BRnzp OVER
        
NONUM   LEA R0, NOD
        TRAP x22    ;" is not a decimal digit."
        
OVER    AND R0, R0, #0
        ADD R0, R0, x000A
        TRAP x21    ;显示换行
        LD R0, SAVER0
        LD R1, SAVER1
        LD R2, SAVER2
        RTI
        
SAVER0 .FILL x0000
SAVER1 .FILL x0000
SAVER2 .FILL x0000
YESD .STRINGZ " is a decimal digit."
NOD .STRINGZ " is not a decimal digit."
HN .FILL x3FFF
        ; *** End interrupt service routine code here ***
        .END