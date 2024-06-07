.section .text
.globl draw
.type draw, @function
draw:
	li a0,10
	li a1,10
	li a2,70
	li a3,50
	li a4,65535
	addi sp,sp,-4
	sw ra,0(sp)
	jal LCD_DrawRectangle    # 执行完就回来
	lw ra,0(sp)
	addi sp,sp,4


## 怎么从C到risc-v传参？