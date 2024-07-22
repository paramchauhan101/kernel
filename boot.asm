[bits 16]
[org 0x7c00]

; Load the kernel
mov ax, 0x1000      ; Segment address for the kernel
mov ds, ax
mov es, ax

; Load the kernel (assumes the kernel is loaded at 0x1000:0x0000)
mov si, 0x0000
mov di, 0x8000
mov cx, 0x1000
rep movsb

; Jump to the kernel
jmp 0x1000:0x0000

; Fill the rest of the boot sector with zeros
times 510 - ($ - $$) db 0
dw 0xaa55
