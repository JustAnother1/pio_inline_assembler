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
#ifndef CLI_CLI_H_
#define CLI_CLI_H_

#include <stdint.h>
#include <stdbool.h>

void cli_init(void);
void cli_tick(void);
bool cmd_help(const uint32_t loop);
void cli_welcome(void);

/** get pointer to command line parameter string.
 *
 * @param parameter_index which parameter is requested
 * @return pointer to a 0 terminated string represented the requested parameter or NULL if no such parameter.
 */
uint8_t* cli_get_parameter(const uint32_t parameter_index);


#endif /* CLI_CLI_H_ */
