#include "x86.h"
#include "screen.h"
#include "pci.h"

uint16_t pci_inw(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;

	address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
	x86_outl(0x0cf8, address);
	tmp = (uint16_t)((x86_inl (0x0cfc) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

void pci_check_device(uint8_t bus, uint8_t device)
{
    uint16_t vendor = pci_inw(bus, device, 0, 0);
    if (vendor != 0xffff) screen_printf("vendor: 0x%x, device: 0x%x\n", vendor, pci_inw(bus, device, 0, 2));
}
