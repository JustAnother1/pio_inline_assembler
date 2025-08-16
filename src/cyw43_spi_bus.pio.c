#include "cyw43_spi_bus.h"
#include "hal/hw/RESETS.h"
#include "hal/hw/PADS_BANK0.h"
#include "hal/hw/IO_BANK0.h"
#include "PIO.h"
#include "hal/hw/PIO0.h"

static const uint16_t cyw43_spi_gap0_sample1_instructions[] = {
/* PIO inline ASM gap0_sample1
;
; Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
;
; SPDX-License-Identifier: BSD-3-Clause
;

.program spi_gap0_sample1
.side_set 1

; always transmit multiple of 32 bytes
lp: out pins, 1             side 0
    jmp x-- lp              side 1
public lp1_end:
    set pindirs, 0          side 0
lp2:
    in pins, 1              side 1
    jmp y-- lp2             side 0
public end:

 PIO inline ASM */
};

static const uint16_t cyw43_spi_gap01_sample0_instructions[] = {
/* PIO inline ASM gap01_sample0

.program spi_gap01_sample0
.side_set 1

; always transmit multiple of 32 bytes
lp: out pins, 1             side 0
    jmp x-- lp              side 1
public lp1_end:
    set pindirs, 0          side 0
    nop                     side 1
lp2:
    in pins, 1              side 0
    jmp y-- lp2             side 1
public end:

 PIO inline ASM */
};

static const uint16_t cyw43_spi_gap010_sample1_instructions[] = {
/* PIO inline ASM gap010_sample1


.program spi_gap010_sample1
.side_set 1

; always transmit multiple of 32 bytes
lp: out pins, 1             side 0
    jmp x-- lp              side 1
public lp1_end:
    set pindirs, 0          side 0
    nop                     side 1
    nop                     side 0
lp2:
    in pins, 1              side 1
    jmp y-- lp2             side 0
public end:

 PIO inline ASM */
};

static const uint16_t cyw43_spi_gap0_sample1_regular_instructions[] = {
/* PIO inline ASM gap0_sample1_regular


.program spi_gap0_sample1_regular
.side_set 1

; always transmit multiple of 32 bytes
lp: out pins, 1             side 0
    jmp x-- lp              side 1
public lp1_end:
    set pindirs, 0          side 0
lp2:
    in pins, 1              side 1
    jmp y-- lp2             side 0
public end:

 PIO inline ASM */
};

bool load_cyw43_spi_bus(const uint32_t loop)
{
    uint32_t i;
    (void) loop;
    RESETS->RESET = RESETS->RESET & ~ RESETS_RESET_IO_BANK0_MASK; // take IO_BANK0 out of Reset
    // load program into PIO
    for(i = 0; i < (sizeof(cyw43_spi_gap0_sample1_instructions)/sizeof(cyw43_spi_gap0_sample1_instructions[0])); i++)
    {
        ((PIO_type*)PIO0)->INSTR_MEM[i] = cyw43_spi_gap0_sample1_instructions[i];
    }

    for(; i < (sizeof(cyw43_spi_gap01_sample0_instructions)/sizeof(cyw43_spi_gap01_sample0_instructions[0])); i++)
    {
        ((PIO_type*)PIO0)->INSTR_MEM[i] = cyw43_spi_gap01_sample0_instructions[i];
    }

    for(; i < (sizeof(cyw43_spi_gap010_sample1_instructions)/sizeof(cyw43_spi_gap010_sample1_instructions[0])); i++)
    {
        ((PIO_type*)PIO0)->INSTR_MEM[i] = cyw43_spi_gap010_sample1_instructions[i];
    }

    for(; i < (sizeof(cyw43_spi_gap0_sample1_regular_instructions)/sizeof(cyw43_spi_gap0_sample1_regular_instructions[0])); i++)
    {
        ((PIO_type*)PIO0)->INSTR_MEM[i] = cyw43_spi_gap0_sample1_regular_instructions[i];
    }
    // device cpu clock by 10 ( 200MHz -> 20 MHz)
    // PIO code uses 4 cycles per cycle of output signal
    // 200MHz / 4 = 50 MHz /2.5 = 20 MHz
    PIO0->SM0_CLKDIV = (uint32_t) (2.5f * (1 << PIO_SM0_CLKDIV_INT_OFFSET));
    // GPIO0
    PIO0->SM0_PINCTRL = (1 << PIO_SM0_PINCTRL_SET_COUNT_OFFSET)
                     | (0 << PIO_SM0_PINCTRL_SET_BASE_OFFSET);
    PADS_BANK0->GPIO0 = (PADS_BANK0_GPIO0_DRIVE_12MA << PADS_BANK0_GPIO0_DRIVE_OFFSET)
                      | (1 << PADS_BANK0_GPIO0_SLEWFAST_OFFSET);
    IO_BANK0->GPIO0_CTRL = 6; // 6 == PIO0; 7 == PIO1

    PIO0->CTRL = 1; // switch on State machine 0
    return true;
}
