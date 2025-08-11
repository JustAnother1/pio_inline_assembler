#include <stdlib.h>
#include "cli/debug_log.h"
#include "cli/cli.h"
#include "hal/hw/PIO0.h"
#include "hal/hw/PIO1.h"


bool cmd_pio_registers(const uint32_t loop)
{

    switch(loop)
    {
    case  0: cli_line("PIO0 SFR:"); break;
    case  1: cli_line("CTRL:              0x%08lx", PIO0->CTRL); break;
    case  2: cli_line("FSTAT:             0x%08lx", PIO0->FSTAT); break;
    case  3: cli_line("FDEBUG:            0x%08lx", PIO0->FDEBUG); break;
    case  4: cli_line("FLEVEL:            0x%08lx", PIO0->FLEVEL); break;
    // TXF0 : TX FIFO state machine 0
    // TXF1 : TX FIFO state machine 1
    // TXF2 : TX FIFO state machine 2
    // TXF3 : TX FIFO state machine 3
    // RXF0 : RX FIFO state machine 0
    // RXF1 : RX FIFO state machine 1
    // RXF2 : RX FIFO state machine 2
    // RXF3 : RX FIFO state machine 3
    case  5: cli_line("IRQ:               0x%08lx", PIO0->IRQ); break;
    case  6: cli_line("IRQ_FORCE:         0x%08lx", PIO0->IRQ_FORCE); break;
    case  7: cli_line("INPUT_SYNC_BYPASS: 0x%08lx", PIO0->INPUT_SYNC_BYPASS); break;
    case  8: cli_line("DBG_PADOUT:        0x%08lx", PIO0->DBG_PADOUT); break;
    case  9: cli_line("DBG_PADOE:         0x%08lx", PIO0->DBG_PADOE); break;
    case 10: cli_line("DBG_CFGINFO:       0x%08lx", PIO0->DBG_CFGINFO); break;
    // INSTR_MEM0 .. INSTR_MEM31
    case 11: cli_line("SM0_CLKDIV:        0x%08lx", PIO0->SM0_CLKDIV); break;
    case 12: cli_line("SM0_EXECCTRL:      0x%08lx", PIO0->SM0_EXECCTRL); break;
    case 13: cli_line("SM0_SHIFTCTRL:     0x%08lx", PIO0->SM0_SHIFTCTRL); break;
    case 14: cli_line("SM0_ADDR:          0x%08lx", PIO0->SM0_ADDR); break;
    case 15: cli_line("SM0_INSTR:         0x%08lx", PIO0->SM0_INSTR); break;
    case 16: cli_line("SM0_PINCTRL:       0x%08lx", PIO0->SM0_PINCTRL); break;
    case 17: cli_line("SM1_CLKDIV:        0x%08lx", PIO0->SM1_CLKDIV); break;
    case 18: cli_line("SM1_EXECCTRL:      0x%08lx", PIO0->SM1_EXECCTRL); break;
    case 19: cli_line("SM1_SHIFTCTRL:     0x%08lx", PIO0->SM1_SHIFTCTRL); break;
    case 20: cli_line("SM1_ADDR:          0x%08lx", PIO0->SM1_ADDR); break;
    case 21: cli_line("SM1_INSTR:         0x%08lx", PIO0->SM1_INSTR); break;
    case 22: cli_line("SM1_PINCTRL:       0x%08lx", PIO0->SM1_PINCTRL); break;
    case 23: cli_line("SM2_CLKDIV:        0x%08lx", PIO0->SM2_CLKDIV); break;
    case 24: cli_line("SM2_EXECCTRL:      0x%08lx", PIO0->SM2_EXECCTRL); break;
    case 25: cli_line("SM2_SHIFTCTRL:     0x%08lx", PIO0->SM2_SHIFTCTRL); break;
    case 26: cli_line("SM2_ADDR:          0x%08lx", PIO0->SM2_ADDR); break;
    case 27: cli_line("SM2_INSTR:         0x%08lx", PIO0->SM2_INSTR); break;
    case 28: cli_line("SM2_PINCTRL:       0x%08lx", PIO0->SM2_PINCTRL); break;
    case 29: cli_line("SM3_CLKDIV:        0x%08lx", PIO0->SM3_CLKDIV); break;
    case 30: cli_line("SM3_EXECCTRL:      0x%08lx", PIO0->SM3_EXECCTRL); break;
    case 31: cli_line("SM3_SHIFTCTRL:     0x%08lx", PIO0->SM3_SHIFTCTRL); break;
    case 32: cli_line("SM3_ADDR:          0x%08lx", PIO0->SM3_ADDR); break;
    case 33: cli_line("SM3_INSTR:         0x%08lx", PIO0->SM3_INSTR); break;
    case 34: cli_line("SM3_PINCTRL:       0x%08lx", PIO0->SM3_PINCTRL); break;
    case 35: cli_line("INTR:              0x%08lx", PIO0->INTR); break;
    case 36: cli_line("IRQ0_INTE:         0x%08lx", PIO0->IRQ0_INTE); break;
    case 37: cli_line("IRQ0_INTF:         0x%08lx", PIO0->IRQ0_INTF); break;
    case 38: cli_line("IRQ0_INTS:         0x%08lx", PIO0->IRQ0_INTS); break;
    case 39: cli_line("IRQ1_INTE:         0x%08lx", PIO0->IRQ1_INTE); break;
    case 40: cli_line("IRQ1_INTF:         0x%08lx", PIO0->IRQ1_INTF); break;
    case 41: cli_line("IRQ1_INTS:         0x%08lx", PIO0->IRQ1_INTS); break;

    case 42: cli_line("PIO1 SFR:"); break;
    case 43: cli_line("CTRL:              0x%08lx", PIO1->CTRL); break;
    case 44: cli_line("FSTAT:             0x%08lx", PIO1->FSTAT); break;
    case 45: cli_line("FDEBUG:            0x%08lx", PIO1->FDEBUG); break;
    case 46: cli_line("FLEVEL:            0x%08lx", PIO1->FLEVEL); break;
    // TXF0 : TX FIFO state machine 0
    // TXF1 : TX FIFO state machine 1
    // TXF2 : TX FIFO state machine 2
    // TXF3 : TX FIFO state machine 3
    // RXF0 : RX FIFO state machine 0
    // RXF1 : RX FIFO state machine 1
    // RXF2 : RX FIFO state machine 2
    // RXF3 : RX FIFO state machine 3
    case 47: cli_line("IRQ:               0x%08lx", PIO1->IRQ); break;
    case 48: cli_line("IRQ_FORCE:         0x%08lx", PIO1->IRQ_FORCE); break;
    case 49: cli_line("INPUT_SYNC_BYPASS: 0x%08lx", PIO1->INPUT_SYNC_BYPASS); break;
    case 50: cli_line("DBG_PADOUT:        0x%08lx", PIO1->DBG_PADOUT); break;
    case 51: cli_line("DBG_PADOE:         0x%08lx", PIO1->DBG_PADOE); break;
    case 52: cli_line("DBG_CFGINFO:       0x%08lx", PIO1->DBG_CFGINFO); break;
    // INSTR_MEM0 .. INSTR_MEM31
    case 53: cli_line("SM0_CLKDIV:        0x%08lx", PIO1->SM0_CLKDIV); break;
    case 54: cli_line("SM0_EXECCTRL:      0x%08lx", PIO1->SM0_EXECCTRL); break;
    case 55: cli_line("SM0_SHIFTCTRL:     0x%08lx", PIO1->SM0_SHIFTCTRL); break;
    case 56: cli_line("SM0_ADDR:          0x%08lx", PIO1->SM0_ADDR); break;
    case 57: cli_line("SM0_INSTR:         0x%08lx", PIO1->SM0_INSTR); break;
    case 58: cli_line("SM0_PINCTRL:       0x%08lx", PIO1->SM0_PINCTRL); break;
    case 59: cli_line("SM1_CLKDIV:        0x%08lx", PIO1->SM1_CLKDIV); break;
    case 60: cli_line("SM1_EXECCTRL:      0x%08lx", PIO1->SM1_EXECCTRL); break;
    case 61: cli_line("SM1_SHIFTCTRL:     0x%08lx", PIO1->SM1_SHIFTCTRL); break;
    case 62: cli_line("SM1_ADDR:          0x%08lx", PIO1->SM1_ADDR); break;
    case 63: cli_line("SM1_INSTR:         0x%08lx", PIO1->SM1_INSTR); break;
    case 64: cli_line("SM1_PINCTRL:       0x%08lx", PIO1->SM1_PINCTRL); break;
    case 65: cli_line("SM2_CLKDIV:        0x%08lx", PIO1->SM2_CLKDIV); break;
    case 66: cli_line("SM2_EXECCTRL:      0x%08lx", PIO1->SM2_EXECCTRL); break;
    case 67: cli_line("SM2_SHIFTCTRL:     0x%08lx", PIO1->SM2_SHIFTCTRL); break;
    case 68: cli_line("SM2_ADDR:          0x%08lx", PIO1->SM2_ADDR); break;
    case 69: cli_line("SM2_INSTR:         0x%08lx", PIO1->SM2_INSTR); break;
    case 70: cli_line("SM2_PINCTRL:       0x%08lx", PIO1->SM2_PINCTRL); break;
    case 71: cli_line("SM3_CLKDIV:        0x%08lx", PIO1->SM3_CLKDIV); break;
    case 72: cli_line("SM3_EXECCTRL:      0x%08lx", PIO1->SM3_EXECCTRL); break;
    case 73: cli_line("SM3_SHIFTCTRL:     0x%08lx", PIO1->SM3_SHIFTCTRL); break;
    case 74: cli_line("SM3_ADDR:          0x%08lx", PIO1->SM3_ADDR); break;
    case 75: cli_line("SM3_INSTR:         0x%08lx", PIO1->SM3_INSTR); break;
    case 76: cli_line("SM3_PINCTRL:       0x%08lx", PIO1->SM3_PINCTRL); break;
    case 77: cli_line("INTR:              0x%08lx", PIO1->INTR); break;
    case 78: cli_line("IRQ0_INTE:         0x%08lx", PIO1->IRQ0_INTE); break;
    case 79: cli_line("IRQ0_INTF:         0x%08lx", PIO1->IRQ0_INTF); break;
    case 80: cli_line("IRQ0_INTS:         0x%08lx", PIO1->IRQ0_INTS); break;
    case 81: cli_line("IRQ1_INTE:         0x%08lx", PIO1->IRQ1_INTE); break;
    case 82: cli_line("IRQ1_INTF:         0x%08lx", PIO1->IRQ1_INTF); break;
    case 83: cli_line("IRQ1_INTS:         0x%08lx", PIO1->IRQ1_INTS); break;
    default: return true;
    }
    return false;
}

bool cmd_pio_stop(const uint32_t loop)
{
    (void) loop;
    PIO0->CTRL = 0;
    PIO1->CTRL = 0;
    return true;
}
