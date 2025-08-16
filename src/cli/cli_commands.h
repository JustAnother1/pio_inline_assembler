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
#ifndef CLI_CLI_COMMANDS_H_
#define CLI_CLI_COMMANDS_H_

#include "cli_cfg.h"
#include "pio_commands.h"
#include "squarewave.h"
#include "cyw43_spi_bus.h"


cmd_typ commands[] = {
        //         11             1         2         3         4         5         6
        //12345678901    123456789012345678901234567890123456789012345678901234567890
        {"help",        "list all available commands", cmd_help},
        {"r",           "list all SFR", cmd_pio_registers},
        {"square",      "output 20MHz on GPIO0", load_square_wave},
        {"stop",        "stop all PIO activity", cmd_pio_stop},
        {"spi",         "load cyw43 spi bus", load_cyw43_spi_bus},
};


#endif /* CLI_CLI_COMMANDS_H_ */
