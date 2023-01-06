.ORIG x3000
LD R0, DATA
LD R7, DATAWR
ADD R0, R0, #-1
        ;选择排序
CHOOSE  ADD R0, R0, #1
        
        LD R3, DATAOVER
        NOT R4, R3
        ADD R4, R4, #1
        ADD R5, R0, R4
        BRzp NEW
        ;与R3比较判断是否选择结束
        
        ADD R1, R0, #0
        LDR R2, R0, #0
        ;选择该轮循环需要比较的值
        ADD R6, R0, #0
        ;初始化最小值地址
        
AGAIN   ADD R1, R1, #1
        
        LD R3, DATAOVER
        NOT R4, R3
        ADD R4, R4, #1
        ADD R5, R1, R4
        BRzp WRITED
        ;与R3比较判断是否结束该次循环
        
        LDR R3, R1, #0

COMPARE NOT R4, R2
        ADD R4, R4, #1
        ADD R5, R3, R4
        ;比较R2, R3
        BRzp AGAIN
        ADD R2, R3, #0
        ;若R3小于最小值R2,更新最小值
        ADD R6, R1, #0
        ;记录最小值地址，以便交换
        BRnzp AGAIN


WRITED  STR R2, R7, #0
        ADD R7, R7, #1
        ;存储地址的指针向后偏移一位

        LDR R2, R0, #0
        STR R2, R6, #0
        ;把R0指向的值交换到最小值处，以便后续比较
        BRnzp CHOOSE
        
        ;开始计算获得A,B的人数
NEW     LD R0, DATAWROVER
        AND R7, R7, #0
        AND R6, R6, #0
        
        ADD R2, R7, #15
        ADD R2, R2, #15
        ADD R2, R2, #15
        ADD R2, R2, #15
        ADD R2, R2, #15
        ADD R2, R2, #10
        ;R2=85
        NOT R2, R2
        ADD R2, R2, #1
        ADD R3, R7, #15
        ADD R3, R3, #15
        ADD R3, R3, #15
        ADD R3, R3, #15
        ADD R3, R3, #15
        ;R3=75
        NOT R3, R3
        ADD R3, R3, #1
        ADD R4, R7, #4
        
COUNTA  LDR R1, R0, #0
        ADD R4, R4, #-1
        BRn COUNTB
        ADD R5, R1, R2
        BRn COUNTAB
        ADD R7, R7, #1
        ;对于分数在85以上且位于前25%
        
COUNTAN ADD R0, R0, #-1
        BRnzp COUNTA
        
COUNTAB ADD R5, R1, R3
        BRn COUNTAN
        ADD R6, R6, #1
        BRnzp COUNTAN
        ;对于分数在75以上85以下且位于前25%
        
COUNTB  ADD R4, R4, #5
COUNTT  LDR R1, R0, #0
        ADD R4, R4, #-1
        BRn OVER
        ADD R5, R1, R3
        BRn COUNTBN
        ADD R6, R6, #1
        ;对于分数在75以上位于前25~50%
COUNTBN ADD R0, R0, #-1
        BRnzp COUNTT
        
OVER    STI R7, NUMA
        STI R6, NUMB
        HALT

DATA .FILL x4000
DATAOVER .FILL x4010
DATAWR .FILL x5000 
DATAWROVER .FILL x500F
NUMA .FILL x5100
NUMB .FILL x5101
.END