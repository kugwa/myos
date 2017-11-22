#include "x86.h"
#include "apic.h"

#define PIT_RELOAD          (1193182 / 100)
#define PIT_RELOAD_LOW      (PIT_RELOAD & 0xff)
#define PIT_RELOAD_HIGH     ((PIT_RELOAD >> 8) & 0xff)

static void pic_remap_mask(void)
{
    // icw1: begin
    x86_outb(0x20, 0x11);
    x86_outb(0xa0, 0x11);
    
    // icw2: remap
    x86_outb(0x21, 0x20);
    x86_outb(0xa1, 0x28);

    // icw3: cascade
    x86_outb(0x21, 0x04);
    x86_outb(0xa1, 0x02);

    // icw4
    x86_outb(0x21, 0x01);
    x86_outb(0xa1, 0x01);

    // init is over, now mask all irqs
    x86_outb(0x21, 0xff);
    x86_outb(0xa1, 0xff);
}

void apic_init()
{
    pic_remap_mask();
    
    // initialize LAPIC to a well known state
    APIC_LOCAL_APIC_REG(APIC_DFR) = 0xffffffff;
    APIC_LOCAL_APIC_REG(APIC_LDR) = (APIC_LOCAL_APIC_REG(APIC_LDR) & 0x00ffffff) | 0x01;
    APIC_LOCAL_APIC_REG(APIC_LVT_TMR) = APIC_DISABLE;
    APIC_LOCAL_APIC_REG(APIC_LVT_PERF) = APIC_NMI;
    APIC_LOCAL_APIC_REG(APIC_LVT_LINT0) = APIC_DISABLE;
    APIC_LOCAL_APIC_REG(APIC_LVT_LINT1) = APIC_DISABLE;
    APIC_LOCAL_APIC_REG(APIC_TASKPRIOR) = 0;

    // software enable LAPIC
    APIC_LOCAL_APIC_REG(APIC_SPURIOUS) = APIC_SW_ENABLE | 0x27;
    APIC_LOCAL_APIC_REG(APIC_LVT_TMR) = 0x20;
    APIC_LOCAL_APIC_REG(APIC_TMRDIV) = 0x3;

    // set PIT reload value
    x86_outb(0x43, 0x34);
    x86_outb(0x40, PIT_RELOAD_LOW);
    x86_outb(0x40, PIT_RELOAD_HIGH);

    // reset LAPIC timer
    APIC_LOCAL_APIC_REG(APIC_TMRINITCNT) = 0xffffffff;
 
    // wait until PIT counter wraps
    while(1) {
        x86_inb(0x40);
        if (x86_inb(0x40) != PIT_RELOAD_HIGH) break;
    }
    while(1) {
        x86_inb(0x40);
        if (x86_inb(0x40) == PIT_RELOAD_HIGH) break;
    }

    // save LAPIC timer remain count
    uint32_t remain_count = APIC_LOCAL_APIC_REG(APIC_TMRCURRCNT);
    APIC_LOCAL_APIC_REG(APIC_LVT_TMR) = APIC_DISABLE;

    // start periodic mode with the correct initial count
    APIC_LOCAL_APIC_REG(APIC_LVT_TMR) = 0x20 | TMR_PERIODIC;
    APIC_LOCAL_APIC_REG(APIC_TMRDIV) = 0x3;
    APIC_LOCAL_APIC_REG(APIC_TMRINITCNT) = (0xffffffff - remain_count) * 100;   // 1 second here
}

