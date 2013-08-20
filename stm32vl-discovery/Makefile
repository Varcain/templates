PROJ_NAME = main

###################################################
# Set toolchain
TC = /home/limak/x-tools/arm-cortex_m3-eabi/bin/arm-cortex_m3-eabi

# Set Tools
CC			= $(TC)-gcc
LD			= $(TC)-ld
AR			= $(TC)-ar
OBJCOPY		= $(TC)-objcopy
OBJDUMP		= $(TC)-objdump
SIZE		= $(TC)-size

###################################################
# Set Sources
LIB_SRCS	= $(wildcard Libraries/STM32F10x_StdPeriph_Driver/src/*.c)
			  
USER_SRCS	= $(wildcard src/*.c) 
ASM_SRCS    = $(wildcard src/*.s)

# Set Include Paths
INCLUDES 	= -ILibraries/STM32F10x_StdPeriph_Driver/inc \
			  -Iinc/
			
# Set Libraries
LIBS		= -lm

# Set Objects
LIB_OBJS	= $(LIB_SRCS:.c=.o)
USER_OBJS	= $(USER_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)

###################################################
# Set Board
DEFINES 	= -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER

# Set Compilation and Linking Flags
CFLAGS 		= $(DEFINES) $(INCLUDES)
CFLAGS		+= -g -Wall -Wno-missing-braces -std=c99 
CFLAGS		+= -O0 -ffunction-sections -fdata-sections -ffast-math -fsingle-precision-constant
CFLAGS		+= -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

ASFLAGS 	= -g -Wa,--warn -x assembler-with-cpp -mcpu=cortex-m3 -mthumb

LDFLAGS 	= -g -Tstm32f100rb_flash.ld $(LIBS) \
			-Xlinker --gc-sections \
			-Wl,-Map,$(PROJ_NAME).map \
			-o $(PROJ_NAME).elf

###################################################
# Default Target
all: $(PROJ_NAME).hex $(PROJ_NAME).lst info

# elf Target
$(PROJ_NAME).elf: $(ASM_OBJS) $(USER_OBJS) $(LIB_OBJS)
	$(CC) $(ASM_OBJS) $(USER_OBJS) $(LIB_OBJS) $(LDFLAGS) 
	@echo $@

# bin Target
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

# Rule for .c files
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo $@

# Rule for .s files
.s.o:
	$(CC) $(ASFLAGS) -c -o $@ $<
	@echo $@

# Clean Target
clean:
	rm -f $(LIB_OBJS)
	rm -f $(USER_OBJS)
	rm -f $(ASM_OBJS)
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst
