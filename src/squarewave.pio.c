#include <stdint.h>
#include "squarewave.h"
#include "hal/hw/RESETS.h"
#include "hal/hw/PADS_BANK0.h"
#include "hal/hw/IO_BANK0.h"
#include "PIO.h"
#include "hal/hw/PIO0.h"


static const uint16_t squarewave_program_instructions[] = {
/* PIO inline ASM
;
; Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
;
; SPDX-License-Identifier: BSD-3-Clause
;
.pio_version 0 // only requires PIO version 0

.program squarewave
    set pindirs, 1   ; Set pin to output
again:
    set pins, 1 [1]  ; Drive pin high and then delay for one cycle
    set pins, 0      ; Drive pin low
    jmp again        ; Set PC to label `again`

 PIO inline ASM */
};

bool load_square_wave(const uint32_t loop)
{
    uint32_t i;
    (void) loop;
    RESETS->RESET = RESETS->RESET & ~ RESETS_RESET_IO_BANK0_MASK; // take IO_BANK0 out of Reset
    // load program into PIO
    for(i = 0; i < (sizeof(squarewave_program_instructions)/sizeof(squarewave_program_instructions[0])); i++)
    {
        ((PIO_type*)PIO0)->INSTR_MEM[i] = squarewave_program_instructions[i];
    }
    // device cpu clock by 10 ( 200MHz -> 20 MHz)
    // PIO code uses 4 cycles per cycle of output signal
    // 200MHz / 4 = 50 MHz /2.5 = 20 MHz
    PIO0->SM0_CLKDIV = (uint32_t) (2.5f * (1 << PIO_SM0_CLKDIV_INT_OFFSET));
    // GPIO0
    PIO0->SM0_PINCTRL = (1 << PIO_SM0_PINCTRL_SET_COUNT_OFFSET)
                     | (0 << PIO_SM0_PINCTRL_SET_BASE_OFFSET);
    PADS_BANK0->GPIO[0] = (PADS_BANK0_GPIO0_DRIVE_12MA << PADS_BANK0_GPIO0_DRIVE_OFFSET)
                      | (1 << PADS_BANK0_GPIO0_SLEWFAST_OFFSET);
    IO_BANK0->GPIO0_CTRL = 6; // 6 == PIO0; 7 == PIO1

    PIO0->CTRL = 1; // switch on State machine 0
    return true;
}
