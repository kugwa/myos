bits 32
section .text

global start
extern init
start:
    mov     esp, stack
    call    init
.halt:
    hlt
    jmp     .halt

    ; multiboot spec
    align   4
    dd      0x1badb002
    dd      0x0
    dd      -(0x1badb002 + 0x0)

global x86_load_gdt_set_selectors
x86_load_gdt_set_selectors:
    mov     ecx, [esp + 4]
    mov     eax, [esp + 8]
    mov     word [ecx], ax
    mov     eax, [esp + 12]
    mov     dword [ecx + 2], eax
    lgdt    [ecx]
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    jmp     0x08:.end
.end:
    ret

global x86_load_idt_sti
x86_load_idt_sti:
    mov     ecx, [esp + 4]
    mov     eax, [esp + 8]
    mov     word [ecx], ax
    mov     eax, [esp + 12]
    mov     dword [ecx + 2], eax
    lidt    [ecx]
    sti
    ret

global x86_save_regs
x86_save_regs:
    mov     dword [saved_regs], eax
    mov     dword [saved_regs + 4], ecx
    mov     dword [saved_regs + 8], edx
    mov     dword [saved_regs + 12], ebx
    mov     dword [saved_regs + 16], esp
    mov     dword [saved_regs + 20], ebp
    mov     dword [saved_regs + 24], esi
    mov     dword [saved_regs + 28], edi
    ret

global x86_get_saved_regs
x86_get_saved_regs:
    mov     eax, saved_regs
    ret

global x86_inb
x86_inb:
    mov     edx, [esp + 4]
    in      al, dx
    ret

global x86_outb
x86_outb:
    mov     edx, [esp + 4]
    mov     eax, [esp + 8]
    out     dx, al
    ret

global x86_inw
x86_inw:
    mov     edx, [esp + 4]
    in      ax, dx
    ret

global x86_outw
x86_outw:
    mov     edx, [esp + 4]
    mov     eax, [esp + 8]
    out     dx, ax
    ret

global x86_inl
x86_inl:
    mov     edx, [esp + 4]
    in      eax, dx
    ret

global x86_outl
x86_outl:
    mov     edx, [esp + 4]
    mov     eax, [esp + 8]
    out     dx, eax
    ret

global x86_cpuid
x86_cpuid:
    mov     eax, [esp + 4]
    xor     ebx, ebx
    xor     ecx, ecx
    xor     edx, edx
    cpuid
    ret

global x86_rdmsr
x86_rdmsr:
    mov     ecx, [esp + 4]
    rdmsr
    ret

global x86_wrmsr
x86_wrmsr:
    mov     ecx, [esp + 4]
    mov     edx, [esp + 8]
    mov     eax, [esp + 12]
    wrmsr
    ret

section .bss
saved_regs:
    resb    32
    resb    8192
stack:
