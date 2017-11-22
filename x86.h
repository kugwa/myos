#include <stdint.h>

#define X86_IDT_ENTRY_ATTR_TRAP     0x8f00
#define X86_IDT_ENTRY_ATTR_INT      0x8e00
#define X86_IDT_ENTRY_ATTR_TASK     0x8500

typedef struct {
    uint8_t     limit_0;
    uint8_t     limit_1;
    uint8_t     base_0;
    uint8_t     base_1;
    uint8_t     base_2;
    uint8_t     attr_0;
    uint8_t     limit_2_attr_1;
    uint8_t     base_3;
} x86_gdt_entry;

typedef struct {
    uint16_t    offset_0;
    uint16_t    selector;
    uint16_t    attr;
    uint16_t    offset_16;
} x86_idt_entry;

typedef struct {
    uint8_t     size_0;
    uint8_t     size_1;
    uint8_t     addr_0;
    uint8_t     addr_1;
    uint8_t     addr_2;
    uint8_t     addr_3;
} x86_table_descriptor;

typedef struct {
    uint32_t    eax;
    uint32_t    ecx;
    uint32_t    edx;
    uint32_t    ebx;
    uint32_t    esp;
    uint32_t    ebp;
    uint32_t    esi;
    uint32_t    edi;
} reg_set;

void        x86_set_gdt_entry           (x86_gdt_entry *entry, uint32_t base, uint32_t limit, uint16_t attr);
void        x86_set_idt_entry           (x86_idt_entry *entry, uint16_t selector, uint32_t offset, uint16_t attr);

void        x86_load_gdt_set_selectors  (x86_table_descriptor *descriptor, uint16_t size, x86_gdt_entry *addr);
void        x86_load_idt_sti            (x86_table_descriptor *descriptor, uint16_t size, x86_idt_entry *addr);
void        x86_save_regs               (void);
reg_set    *x86_get_saved_regs          (void);
uint8_t     x86_inb                     (uint16_t port);
void        x86_outb                    (uint16_t port, uint8_t data);
uint16_t    x86_inw                     (uint16_t port);
void        x86_outw                    (uint16_t port, uint16_t data);
uint32_t    x86_inl                     (uint16_t port);
void        x86_outl                    (uint16_t port, uint32_t data);
void        x86_cpuid                   (uint32_t eax);
void        x86_rdmsr                   (uint32_t ecx);
void        x86_wrmsr                   (uint32_t ecx, uint32_t edx, uint32_t eax);
