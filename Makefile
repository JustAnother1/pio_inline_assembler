# Makefile for the PIO test firmware
# ==================================

project = test_pio

# tools
# =====
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
SIZE = size
MKDIR_P = mkdir -p
INLPIO = tools/compile_inline_pio_asm.py

# configuration
# =============
BIN_FOLDER = bin/
SRC_FOLDER = src/
LKR_SCRIPT = $(SRC_FOLDER)hal/RP2040.ld
ifeq ($(CLI), uart)
# CLI on UART
DDEFS = -DFEAT_DEBUG_UART
else
# CLI on USB-CDC
DDEFS = -DFEAT_DEBUG_CDC
endif



SRC += $(SRC_FOLDER)main.c
# CLI
SRC += $(SRC_FOLDER)cli/cli.c
SRC += $(SRC_FOLDER)pio_commands.c
SRC += $(SRC_FOLDER)squarewave.binpio.c
SRC += $(SRC_FOLDER)cyw43_spi_bus.binpio.c

ifeq ($(CLI), uart)
# CLI on UART
SRC += $(SRC_FOLDER)hal/debug_uart.c
else
# USB driver
SRC += $(SRC_FOLDER)tinyusb/usb.c
SRC += $(SRC_FOLDER)tinyusb/usb_descriptors.c

# USB stack (tinyusb
SRC += $(SRC_FOLDER)tinyusb/src/tusb.c
SRC += $(SRC_FOLDER)tinyusb/src/device/usbd.c
SRC += $(SRC_FOLDER)tinyusb/src/device/usbd_control.c
SRC += $(SRC_FOLDER)tinyusb/src/common/tusb_fifo.c

# USB serial interface (CDC)
SRC += $(SRC_FOLDER)tinyusb/usb_cdc.c
SRC += $(SRC_FOLDER)tinyusb/src/class/cdc/cdc_device.c
endif
# functions usually available from standard libraries
SRC += $(SRC_FOLDER)lib/ctype.c
SRC += $(SRC_FOLDER)lib/atoi.c
SRC += $(SRC_FOLDER)lib/memcmp.c
SRC += $(SRC_FOLDER)lib/memcpy.c
SRC += $(SRC_FOLDER)lib/memmove.c
SRC += $(SRC_FOLDER)lib/memset.c
SRC += $(SRC_FOLDER)lib/printf.c
SRC += $(SRC_FOLDER)lib/strchr.c
SRC += $(SRC_FOLDER)lib/strlen.c
SRC += $(SRC_FOLDER)lib/strncmp.c

SRC += $(SRC_FOLDER)hal/hw_divider.c
# MBSP
SRC += $(SRC_FOLDER)hal/startup.c
SRC += $(SRC_FOLDER)hal/irq.c

SRC += $(SRC_FOLDER)hal/pios.c

INCDIRS +=$(SRC_FOLDER)
INCDIRS +=$(BIN_FOLDER)
ifeq ($(CLI), uart)
else
INCDIRS +=$(SRC_FOLDER)tinyusb/
INCDIRS +=$(SRC_FOLDER)tinyusb/src/
endif

CFLAGS  = -c -ggdb3 -MMD -MP
CFLAGS += -O3
# sometimes helps with debugging:
# CFLAGS += -O0
# CFLAGS += -save-temps=obj

CFLAGS += -std=c17
CFLAGS += -mcpu=cortex-m0plus -mthumb
CFLAGS += -ffreestanding -funsigned-char
# -fno-short-enums
CFLAGS += -Wall -Wextra -pedantic -Wshadow -Wdouble-promotion -Wconversion
# -Wpadded : tinyUSB creates warnings with this enabled. :-(
CFLAGS += -ffunction-sections -fdata-sections


LFLAGS  = -ffreestanding -nostartfiles
# disabled the following due to this issue:
#  undefined reference to `__gnu_thumb1_case_si'
#LFLAGS += -nostdlib -nolibc -nodefaultlibs
LFLAGS += -specs=nosys.specs
#LFLAGS += -fno-builtin -fno-builtin-function
# https://wiki.osdev.org/Libgcc : All code compiled with GCC must be linked with libgcc.
LFLAGS += -lgcc
LFLAGS += -Wl,--gc-sections,-Map=$(BIN_FOLDER)$(PROJECT).map,--print-memory-usage -g
LFLAGS += -fno-common -T$(LKR_SCRIPT)

GITREF = $(shell cd $(NOMAGIC_FOLDER) && git describe --abbrev=40 --dirty --always --tags)
OBJS = $(addprefix $(BIN_FOLDER),$(SRC:.c=.o))
INCDIR = $(patsubst %,-I%, $(INCDIRS))

# make config
.DEFAULT_GOAL = all

# targets
# =======
help:
	@echo "test pio firmware"
	@echo "available targets"
	@echo "================="
	@echo "make clean              delete all generated files"
	@echo "make all                compile firmware creates elf and uf2 file."
	@echo "make all CLI=uart       - with the interface on the UART"
	@echo "make flash              write firmware to flash of RP2040"
	@echo "                        using openocd and CMSIS-DAP adapter(picoprobe)"
	@echo ""

$(BIN_FOLDER)version.h:
	@echo ""
	@echo "create version.h"
	@echo "================"
	@echo -n "#define VERSION \"" > $(BIN_FOLDER)version.h
	@echo "$(GITREF)\"" >> $(BIN_FOLDER)version.h
	@cat $(BIN_FOLDER)version.h

$(BIN_FOLDER)$(project).elf: $(OBJS)
	@echo ""
	@echo "linking"
	@echo "======="
	$(LD) $(LFLAGS) -o $(BIN_FOLDER)$(project).elf $(OBJS)

flash: $(BIN_FOLDER)$(project).elf
	@echo ""
	@echo "flashing"
	@echo "========"
	openocd  -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program $(BIN_FOLDER)$(project).elf verify reset exit"

$(BIN_FOLDER)$(project).uf2: $(BIN_FOLDER)$(project).elf
	@echo ""
	@echo "elf -> uf2"
	@echo "=========="
	elf2uf2 -f 0xe48bff56 -p 256 -i $(BIN_FOLDER)$(project).elf

all: $(BIN_FOLDER)$(project).uf2
	@echo ""
	@echo "size"
	@echo "===="
	$(SIZE)  --format=GNU $(BIN_FOLDER)$(project).elf

$(BIN_FOLDER)src/cli/cli.o: src/cli/cli.c $(BIN_FOLDER)version.h
	@echo ""
	@echo "=== compiling (cli) $@"
	@$(MKDIR_P) $(@D)
	$(CC) -c $(CFLAGS) $(DDEFS) $(INCDIR) $< -o $@

%.binpio.c : %.pio.c
	@echo ""
	@echo "=== compiling $@"
	$(INLPIO) $<

$(BIN_FOLDER)%.o: %.c
	@echo ""
	@echo "=== compiling $@"
	@$(MKDIR_P) $(@D)
	$(CC) -c $(CFLAGS) $(DDEFS) $(INCDIR) $< -o $@

clean:
	rm -rf $(BIN_FOLDER)* */*.binpio.c */*.inl.pio

.PHONY: clean flash all

-include $(OBJS:.o=.d)
