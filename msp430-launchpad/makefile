# Copyright (C) 2018  Kamil Lulko <kamil.lulko@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


############################################################################
# User configurables
############################################################################

PROJ_NAME	= blink

# Set toolchain
MSP430_GCC_PATH	= /home/varcain/tools/toolchains/msp430-gcc
CROSS_COMPILE	= msp430-elf

# Add individual .c files
C_SRCS		= \

# Add full source dirs (all contained .c and .s files will be added)
SRC_DIRS	= \
		src \

# Filter out specific .c files (use to exclude specific .c files from above)
FILTER_ENTRIES	= \

INCLUDES	+= \
		-I$(MSP430_GCC_PATH)/include

MCU		= msp430g2231

USER_CFLAGS	= -g -O0

# mspdebug driver
DBG_IFACE	= rf2500

############################################################################
# Internal (usually do not edit)
############################################################################

# Output paths
OBJ_DIR		= obj
DEP_DIR		= dep
OUT_DIR		= out

PROJ_NAME	:= $(addprefix $(OUT_DIR)/, $(PROJ_NAME))

# Set Tools
CC		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-gcc
LD		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-ld
AS		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-gcc
OBJCOPY		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-objcopy
OBJDUMP		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-objdump
SIZE		= $(MSP430_GCC_PATH)/bin/$(CROSS_COMPILE)-size

# Set Compilation and Linking Flags
CFLAGS	= -mmcu=$(MCU) $(USER_CFLAGS) -Wall -Wunused $(INCLUDES)
ASFLAGS	= -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS	= -mmcu=$(MCU) -Wl,-Map=$(PROJ_NAME).map -L $(MSP430_GCC_PATH)/include

C_SRCS_DIRS = $(sort $(dir $(C_SRCS)))

C_SRCS += $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*.c))
S_SRCS := $(foreach dir, $(SRC_DIRS),$(wildcard $(dir)/*.s))

C_SRCS := $(filter-out $(FILTER_ENTRIES),$(C_SRCS))

# Dir fixup
SRC_DIRS += $(C_SRCS_DIRS)

OBJS := $(foreach src, $(C_SRCS),$(addprefix $(OBJ_DIR)/,$(notdir $(C_SRCS:.c=.o))))
OBJS += $(foreach src, $(S_SRCS),$(addprefix $(OBJ_DIR)/,$(notdir $(S_SRCS:.s=.o))))

DEPS := $(foreach src, $(C_SRCS),$(addprefix $(DEP_DIR)/,$(notdir $(C_SRCS:.c=.d))))
DEPS += $(foreach src, $(S_SRCS),$(addprefix $(DEP_DIR)/,$(notdir $(S_SRCS:.s=.d))))

all: mkdir $(PROJ_NAME).hex $(PROJ_NAME).lst $(DEPS) info

$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo $@

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	@echo $@

$(PROJ_NAME).hex: $(PROJ_NAME).elf
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	@echo $@

$(PROJ_NAME).lst: $(PROJ_NAME).elf
	@$(OBJDUMP) -h -S $(PROJ_NAME).elf > $(PROJ_NAME).lst
	@echo $@

# Display Memory Usage Info
info: $(PROJ_NAME).elf
	@$(SIZE) --format=berkeley $(PROJ_NAME).elf

vpath %.c $(SRC_DIRS)
vpath %.s $(SRC_DIRS)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

$(OBJ_DIR)/%.o: %.s
	$(CC) $(ASFLAGS) -c -o $@ $<
	@echo $@

$(DEP_DIR)/%.d: %.c
	$(CC) -M ${CFLAGS} $< >$@
	@echo $@

mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	@mkdir -p $(OUT_DIR)

# debug tool to print variables
#print-%  : ; @echo $* = $($*)

flash: all
	@mspdebug $(DBG_IFACE) "prog $(PROJ_NAME).elf"

.SILENT:
.PHONY:	clean
clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR) $(OUT_DIR)
