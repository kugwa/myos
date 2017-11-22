#include <stdint.h>
#include "x86.h"
#include "apic.h"
#include "screen.h"

#define GDT_ENTRY_NUM   3
#define IDT_ENTRY_NUM   256

x86_gdt_entry gdt[GDT_ENTRY_NUM];
x86_table_descriptor descriptor_gdt;

x86_idt_entry idt[IDT_ENTRY_NUM];
x86_table_descriptor descriptor_idt;

static void setup_descriptor()
{
    int i;

    x86_set_gdt_entry(gdt, 0, 0, 0);
    x86_set_gdt_entry(gdt + 1, 0, 0xfffff, 0xc09a);
    x86_set_gdt_entry(gdt + 2, 0, 0xfffff, 0xc092);
    x86_load_gdt_set_selectors(&descriptor_gdt, GDT_ENTRY_NUM * sizeof(x86_gdt_entry), gdt);

    for (i = 0; i < IDT_ENTRY_NUM; i++) {
        x86_set_idt_entry(&idt[i], 0x08, (uint32_t)apic_default_isr, X86_IDT_ENTRY_ATTR_INT);
    }
    x86_set_idt_entry(&idt[0x20], 0x08, (uint32_t)apic_tick_isr, X86_IDT_ENTRY_ATTR_INT);
    x86_set_idt_entry(&idt[0x27], 0x08, (uint32_t)apic_spurious_isr, X86_IDT_ENTRY_ATTR_INT);
    apic_init();
    x86_load_idt_sti(&descriptor_idt, IDT_ENTRY_NUM * sizeof(x86_idt_entry), idt);
}

extern void main();

void init()
{
    // give some time for the debugger to connect
    // for (i = 0; i < 1000000000; i++) ;

    screen_clear();
    setup_descriptor();
    main();
}
