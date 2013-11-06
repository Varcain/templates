 #
 # Makefile for msp430
 #
 # 'make' builds everything
 # 'make clean' deletes everything except source files and Makefile
 # You need to set TARGET, MCU and SOURCES for your project.
 # TARGET is the name of the executable file to be produced 
 # $(TARGET).elf $(TARGET).hex and $(TARGET).txt nad $(TARGET).map are all generated.
 # The TXT file is used for BSL loading, the ELF can be used for JTAG use
 # 
 TARGET     = template
 MCU        = msp430g2231
 # List all the source files here
 # eg if you have a source file foo.c then list it here
 SOURCES = launchpad.c
 # Include are located in the Include directory
 INCLUDES = -IInclude
 # Add or subtract whatever MSPGCC flags you want. There are plenty more
 #######################################################################################
 CFLAGS   = -mmcu=$(MCU) -g -Os -Wall -Wunused $(INCLUDES)   
 ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
 LDFLAGS  = -mmcu=$(MCU) -Wl,-Map=$(TARGET).map
 ########################################################################################
 # x-tools prefix
 XTOOLS   = /home/limak/x-tools/msp430/bin/
 CC       = $(XTOOLS)msp430-gcc
 LD       = $(XTOOLS)msp430-ld
 AR       = $(XTOOLS)msp430-ar
 AS       = $(XTOOLS)msp430-gcc
 GASP     = $(XTOOLS)msp430-gasp
 NM       = $(XTOOLS)msp430-nm
 OBJCOPY  = $(XTOOLS)msp430-objcopy
 RANLIB   = $(XTOOLS)msp430-ranlib
 STRIP    = $(XTOOLS)msp430-strip
 SIZE     = $(XTOOLS)msp430-size
 READELF  = $(XTOOLS)msp430-readelf
 MAKETXT  = srec_cat
 CP       = cp -p
 RM       = rm -f
 MV       = mv
 ########################################################################################
 # the file which will include dependencies
 DEPEND = $(SOURCES:.c=.d)
 # all the object files
 OBJECTS = $(SOURCES:.c=.o)
 all: $(TARGET).elf $(TARGET).hex $(TARGET).txt 
 $(TARGET).elf: $(OBJECTS)
	echo "Linking $@"
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	echo
	echo ">>>> Size of Firmware <<<<"
	$(SIZE) $(TARGET).elf
	echo
 %.hex: %.elf
	$(OBJCOPY) -O ihex $< $@
 %.txt: %.hex
	$(MAKETXT) -O $@ -TITXT $< -I
	unix2dos $(TARGET).txt
 #  The above line is required for the DOS based TI BSL tool to be able to read the txt file generated from linux/unix systems.
 %.o: %.c
	echo "Compiling $<"
	$(CC) -c $(CFLAGS) -o $@ $<
 # rule for making assembler source listing, to see the code
 %.lst: %.c
	$(CC) -c $(ASFLAGS) -Wa,-anlhd $< > $@
 # include the dependencies unless we're going to clean, then forget about them.
 ifneq ($(MAKECMDGOALS), clean)
 -include $(DEPEND)
 endif
 # dependencies file
 # includes also considered, since some of these are our own
 # (otherwise use -MM instead of -M)
 %.d: %.c
	echo "Generating dependencies $@ from $<"
	$(CC) -M ${CFLAGS} $< >$@
 .SILENT:
 .PHONY:	clean
 clean:
	-$(RM) $(OBJECTS)
	-$(RM) $(TARGET).*
	-$(RM) $(SOURCES:.c=.lst)
	-$(RM) $(DEPEND)