#include <stdint.h>
#include "screen.h"
#include "pci.h"

void main()
{
    int b, d;
    for (b = 0; b < 256; b++) for (d = 0; d < 32; d++) {
        pci_check_device(b, d);
    }
}
