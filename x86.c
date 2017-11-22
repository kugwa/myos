#include <stdint.h>
#include "x86.h"

void x86_set_gdt_entry(x86_gdt_entry *entry, uint32_t base, uint32_t limit, uint16_t attr)
{
    entry->limit_0 = (uint8_t)(limit & 0xff);
    entry->limit_1 = (uint8_t)((limit >> 8) & 0xff);
    entry->base_0 = (uint8_t)(base & 0xff);
    entry->base_1 = (uint8_t)((base >> 8) & 0xff);
    entry->base_2 = (uint8_t)((base >> 16) & 0xff);
    entry->attr_0 = (uint8_t)(attr & 0xff);
    entry->limit_2_attr_1 = (uint8_t)(((limit >> 16) & 0x0f) | ((attr >> 8) & 0xf0));
    entry->base_3 = (uint8_t)((base >> 24) & 0xff);
}

void x86_set_idt_entry(x86_idt_entry *entry, uint16_t selector, uint32_t offset, uint16_t attr)
{
    entry->offset_0 = (uint16_t)(offset & 0xffff);
    entry->selector = selector;
    entry->attr = attr;
    entry->offset_16 = (uint16_t)(offset >> 16);
}
