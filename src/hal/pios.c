#include "pios.h"
#include <hal/hw/PSM.h>
#include <hal/hw/RESETS.h>

void init_pios(void)
{
    RESETS->RESET = RESETS->RESET & ~((uint32_t)(1<< RESETS_RESET_IO_BANK0_OFFSET)); // take IO_BANK0 out of Reset
    PSM->FRCE_ON = PSM->FRCE_ON | (1<<PSM_FRCE_ON_SIO_OFFSET); // make sure that SIO is powered on

    RESETS->RESET = RESETS->RESET & ~(1ul << RESETS_RESET_SYSCFG_OFFSET);
    while (0 == ((1 << RESETS_RESET_SYSCFG_OFFSET) & RESETS->RESET_DONE))
    {
        ;
    }

    // take PIOs out of Reset
    RESETS->RESET = RESETS->RESET & ~((1ul << RESETS_RESET_PIO0_OFFSET) | (1ul << RESETS_RESET_PIO1_OFFSET));
    while (0 == (((1 << RESETS_RESET_PIO0_OFFSET) | (1 << RESETS_RESET_PIO0_OFFSET)) & RESETS->RESET_DONE))
    {
        ;
    }

    // NVIC_EnableIRQ(7, 0);  // PIO0-IRQ0
    // NVIC_EnableIRQ(8, 0); // PIO0-IRQ1
    // NVIC_EnableIRQ(9, 0); // PIO1-IRQ0
    // NVIC_EnableIRQ(10, 0); // PIO1-IRQ1
}
