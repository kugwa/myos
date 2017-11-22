#include <stdint.h>

uint16_t pci_inw(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void pci_check_device(uint8_t bus, uint8_t device);
