#define APIC_IA32_APIC_BASE_MSR     0x1b
#define APIC_LOCAL_APIC_BASE        0xfee00000
#define APIC_LOCAL_APIC_REG(reg)    (*(uint32_t*)((APIC_LOCAL_APIC_BASE) + (reg)))

#define APIC_APICID                 0x20
#define APIC_APICVER                0x30
#define APIC_TASKPRIOR              0x80
#define APIC_EOI                    0xb0
#define APIC_LDR                    0xd0
#define APIC_DFR                    0xe0
#define APIC_SPURIOUS               0xf0
#define APIC_ESR                    0x280
#define APIC_ICRL                   0x300
#define APIC_ICRH                   0x310
#define APIC_LVT_TMR                0x320
#define APIC_LVT_PERF               0x340
#define APIC_LVT_LINT0              0x350
#define APIC_LVT_LINT1              0x360
#define APIC_LVT_ERR                0x370
#define APIC_TMRINITCNT             0x380
#define APIC_TMRCURRCNT             0x390
#define APIC_TMRDIV                 0x3e0
#define APIC_LAST                   0x38f
#define APIC_DISABLE                0x10000
#define APIC_SW_ENABLE              0x100
#define APIC_CPUFOCUS               0x200
#define APIC_NMI                    (4 << 8)
#define TMR_PERIODIC                0x20000
#define TMR_BASEDIV                 (1 << 20)

void apic_init();

void apic_default_isr(void);
void apic_spurious_isr(void);
void apic_tick_isr(void);
void apic_sw_int(void);
