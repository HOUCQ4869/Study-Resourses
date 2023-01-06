    .ORIG x3000
    LDI  R0, PPTR
    LDI  R1, QPTR
    LDI  R2, NPTR
    ADD R5, R5, #1
    ADD R6, R6, #1
    ADD R2, R2, #-2
    ;赋初值,N-2便于跳出
    BRn STORE
    
AGAIN   ADD R3, R5, #0
        ADD R4, R6, #0
        ADD R5, R4, #0
    ;R3,R4储存F(N-1),F(N-2),R5记录便于下一个循环使用
    NOT R7, R0
    ADD R7, R7, #1
SUBA  ADD R3, R3, R7
        BRzp SUBA
    ;对p取模
    NOT R7, R1
    ADD R7, R7, #1
SUBB  ADD R4, R4, R7
        BRzp SUBB
    ;对q取模
    ADD R3, R3, R0
    ADD R4, R4, R1
    ;取模后的负值再加上原值
    ADD R6, R3, R4
    ADD R2, R2, #-1
    BRzp AGAIN
    ;根据N值判断是否循环
STORE STI R6, RESULT
    TRAP x25
    ;HALT
    PPTR    .FILL   x3100
    QPTR    .FILL   x3101
    NPTR    .FILL   x3102
    RESULT     .FILL   x3103
    .END
    
    