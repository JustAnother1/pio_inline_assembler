/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include "cli/cli.h"
#include "cli/serial_cfg.h"
#include "hal/debug_uart.h"
#ifdef FEAT_DEBUG_CDC
#include "tinyusb/usb.h"
#endif
#include "lib/printf.h"
#include "hal/pios.h"


int main(void)
{
    init_printf(NULL, serial_debug_putc);
#ifdef FEAT_DEBUG_CDC
    usb_init();
#endif
    cli_init();
    init_pios();

    for(;;)
    {
#ifdef FEAT_DEBUG_UART
        debug_uart_tick();
#endif
#ifdef FEAT_DEBUG_CDC
        usb_tick();
#endif
        cli_tick();
    }
}

