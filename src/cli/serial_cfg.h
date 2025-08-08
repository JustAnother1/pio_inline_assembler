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

#ifndef NOMAGIC_PROBE_SRC_CFG_SERIAL_CFG_H_
#define NOMAGIC_PROBE_SRC_CFG_SERIAL_CFG_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef FEAT_DEBUG_UART
#include "hal/debug_uart.h"
#endif
#ifdef FEAT_DEBUG_CDC
#include "tinyusb/usb_cdc.h"
#include "tinyusb/src/class/cdc/cdc_device.h"
#endif

// DEBUG CLI interface
#ifdef FEAT_DEBUG_UART
#define serial_debug_send_string              debug_uart_send_string
#define serial_debug_send_bytes               debug_uart_send_bytes
#define serial_debug_get_num_received_bytes   debug_uart_get_num_received_bytes
#define serial_debug_get_next_received_byte   debug_uart_get_next_received_byte
#define serial_debug_putc                     debug_uart_putc
#endif

#ifdef FEAT_DEBUG_CDC
#define serial_debug_send_string              usb_cdc_send_string
#define serial_debug_send_bytes               usb_cdc_send_bytes
#define serial_debug_get_num_received_bytes   usb_cdc_get_num_received_bytes
#define serial_debug_get_next_received_byte   usb_cdc_get_next_received_byte
#define serial_debug_putc                     usb_cdc_putc
#endif


#endif /* NOMAGIC_PROBE_SRC_CFG_SERIAL_CFG_H_ */
