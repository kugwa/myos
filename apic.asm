    extern  screen_printf
    global  apic_default_isr
    global  apic_spurious_isr
    global  apic_tick_isr
    global  apic_sw_int

LOCAL_APIC_BASE equ 0xfee00000

section .data
    msg_default_isr:
    db      "=====default_isr====", 0x0a, 0
    msg_spurious_isr:
    db      "====spurious_isr====", 0x0a, 0
    msg_tick_isr:
    db      "======tick_isr======", 0x0a, 0

section .text
bits 32
apic_default_isr:
    push    msg_default_isr
    call    screen_printf
    add     esp, 4
    mov     dword [LOCAL_APIC_BASE + 0xb0], 0x00
    iret

apic_spurious_isr:
    push    msg_spurious_isr
    call    screen_printf
    add     esp, 4
    iret

apic_tick_isr:
    ; push    msg_tick_isr
    ; call    screen_printf
    ; add     esp, 4
    mov     dword [LOCAL_APIC_BASE + 0xb0], 0x00
    iret

apic_sw_int:
    int     0x21
    ret
