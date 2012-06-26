# MCU name
#MCU = atmega1281
MCU = atmega1280


# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#F_CPU = 11059200
F_CPU = 14745600


# Output format. (can be srec, ihex, binary)
FORMAT = ihex


# Target file name (without extension).
TARGET = CSHPZ

#DDEBUG = 1

vpath %.cpp ../../scmRTOS/Common ../../scmRTOS/Lib/AVR-GCC ../../scmRTOS/Target/AVR-GCC
vpath %.S ../../scmRTOS/Common ../../scmRTOS/Lib/AVR-GCC ../../scmRTOS/Target/AVR-GCC
vpath %.cpp ../../Devs
# List C source files here. (C dependencies are automatically generated.)
OBJ = main.o OS_Kernel.o OS_Services.o Usrlib.o OS_Target_cpp.o OS_Target_asm.o \
		Peripheral.o Uart.o Iic.o TechObj.o Devs.o Menu.o Pdz.o \
		Test.o Sgwork.o Dev_VZK.o CSHPZ.o SHPZ_02.o SHPZ_3.o SHPZ_6.o SHPZ_9.o \
		SHPZ_11.o SHPZ_14.o SHPZ_16.o SHPZ_18.o SHPZ_20.o SHPZ_21.o
		#SHPZ_14.o \
		#SHPZ_6.o
		#SHPZ_9.o \
		#SHPZ_14.o
# Optimization level, can be [0, 1, 2, 3, s].
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = 2


# Debugging format.
#     Native formats for AVR-GCC's -g are dwarf-2 [default] or stabs.
#     AVR Studio 4.10 requires dwarf-2.
#     AVR [Extended] COFF format requires stabs, plus an avr-objcopy run.
DEBUG = stabs


# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRAINCDIRS =

VERSEP = ___

#SHELL_HG_IDENTIFY := $(shell hg identify)
#SHELL_HG_TEMPLATE := $(shell hg parent --template "{latesttag}+{latesttagdistance}")
#smhm := $(TARGET)$(VERSEP)$(SHELL_HG_TEMPLATE)$(VERSEP)$(SHELL_HG_IDENTIFY)
SHELL_IDENTIFY := $(shell git show -s --format="%H")
SHELL_TEMPLATE := $(shell sh ../../version_gen.sh )
smhm := $(TARGET)$(VERSEP)$(SHELL_TEMPLATE)$(VERSEP)$(SHELL_IDENTIFY)
# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)UL
CDEFS += -D IDENTIFY="\"$(SHELL_IDENTIFY)\""
CDEFS += -D TEMPLATE="\"$(SHELL_TEMPLATE)\""
CDEFS += -D scmRTOS_PROCESS_COUNT=4
CDEFS += -D scmRTOS_MEM_BLOCK_SIZE=8
CDEFS += -D scmRTOS_MEM_POOL_CAPACITY=8
CDEFS += -D UART0_MASTER=1
ifeq ($(DDEBUG),1)
CDEFS += -D DDEBUG
endif
CDEFS += -D scmRTOS_SYSTIMER_NEST_INTS_ENABLE

# Place -I options here
CINCS = -I../Src -I../../scmRTOS/Common -I../../scmRTOS/Lib/AVR-GCC -I../../scmRTOS/Target/AVR-GCC


# Compiler flags to generate dependency files.
GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d

#---------------- Compiler Options ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT)
#CFLAGS += -ffunction-sections
#CFLAGS += -fdata-sections
CFLAGS += -ffixed-r4  -ffixed-r5  -ffixed-r6  -ffixed-r7  -ffixed-r8  -ffixed-r9
CFLAGS += -ffixed-r10 -ffixed-r11 -ffixed-r12 -ffixed-r13 -ffixed-r14 -ffixed-r15
CFLAGS += -Wa,-adhlns=$(<F:.cpp=.lst)
#CFLAGS += -Wall
CFLAGS += $(GENDEPFLAGS)
#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-adhlns=$(<F:.S=.lst),-gstabs

#---------------- Library Options ----------------
# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
PRINTF_LIB =
#PRINTF_LIB = $(PRINTF_LIB_MIN)
#PRINTF_LIB = $(PRINTF_LIB_FLOAT)


# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
SCANF_LIB =
#SCANF_LIB = $(SCANF_LIB_MIN)
#SCANF_LIB = $(SCANF_LIB_FLOAT)


MATH_LIB = -lm



#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--defsym=__heap_start=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =



#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)
LDFLAGS = -T linker.ld
#LDFLAGS += -Wl,-gc-sections
#ifeq ($(F_CPU),atmega1280)
#LDFLAGS = -T linker.ld

#endif

#---------------- Programming Options (avrdude) ----------------
#---------------- Debugging Options ----------------
#============================================================================

# Define programs and commands.
SHELL = sh
CC = avr-c++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
REMOVEDIR = rmdir
COPY = cp
WINSHELL = cmd
#MERCURIAL = hg
#HG_IDENTIFY_e = hg identify

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = -={ Let\`s mortal combat begin! 11111}=-
MSG_END = - I zili oni dolgo i schaslivo. The end ! -
MSG_SIZE_BEFORE = Size before:
MSG_SIZE_AFTER = Size after:
MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:
MSG_FLASH = Creating load file for Flash:
MSG_EEPROM = Creating load file for EEPROM:
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:

# Define all listing files.
LST = $(OBJ:.o=.lst)


# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU)  $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU)  -x assembler-with-cpp $(ASFLAGS)





# Default target.
all: begin gccversion sizebefore build copir sizeafter end

build: elf hex eep lss sym
#coff
# extcoff

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep
lss: $(TARGET).lss
sym: $(TARGET).sym
cof: $(TARGET).cof


# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

copir:
	@echo
	@echo $(MSG_BEGIN)
	$(shell mkdir -p ../../hexout)
	$(COPY) $(TARGET).hex ../../hexout/'$(smhm)'.hex

end:
	#@echo $(MSG_END)



# Display size of file.
#HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf
AVRMEM =./avr-mem.sh $(TARGET).elf $(MCU)
#AVRMEM = $(SIZE) -C $(TARGET).elf
sizebefore:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); \
	$(AVRMEM) 2>/dev/null; echo; fi

sizeafter:
	@if test -f $(TARGET).elf; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); $(HEXSIZE) \
	$(AVRMEM) 2>/dev/null; fi



# Display compiler version information.
gccversion :
	@$(CC) --version

# Generate avr-gdb config/init file which does the following:
#     define the reset signal, load the target file, connect to target, and set
#     a breakpoint at main().
gdb-config:
	@$(REMOVE) $(GDBINIT_FILE)
	@echo define reset >> $(GDBINIT_FILE)
	@echo SIGNAL SIGHUP >> $(GDBINIT_FILE)
	@echo end >> $(GDBINIT_FILE)
	@echo file $(TARGET).elf >> $(GDBINIT_FILE)
	@echo target remote $(DEBUG_HOST):$(DEBUG_PORT)  >> $(GDBINIT_FILE)
ifeq ($(DEBUG_BACKEND),simulavr)
	@echo load  >> $(GDBINIT_FILE)
endif
	@echo break main >> $(GDBINIT_FILE)

debug: gdb-config $(TARGET).elf
ifeq ($(DEBUG_BACKEND), avarice)
	@echo Starting AVaRICE - Press enter when "waiting to connect" message displays.
	@$(WINSHELL) /c start avarice --jtag $(JTAG_DEV) --erase --program --file \
	$(TARGET).elf $(DEBUG_HOST):$(DEBUG_PORT)
	@$(WINSHELL) /c pause

else
	@$(WINSHELL) /c start simulavr --gdbserver --device $(MCU) --clock-freq \
	$(DEBUG_MFREQ) --port $(DEBUG_PORT)
endif
	@$(WINSHELL) /c start avr-$(DEBUG_UI) --command=$(GDBINIT_FILE)




# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000


coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

#	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< ryba.hex

%.eep: %.elf
	@echo
	@echo $(MSG_EEPROM) $@
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n --print-size $< > $@



# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)


# Compile: create object files from C source files.
%.o : %.cpp
#	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.cpp
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
#	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Create preprocessed source for use in sending a bug report.
%.i : %.cpp
	$(CC) -E -mmcu=$(MCU) $(CFLAGS) $< -o $@


# Target: clean project.
clean: begin clean_list end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) *.hex
	$(REMOVE) *.eep
	$(REMOVE) *.cof
	$(REMOVE) *.elf
	$(REMOVE) *.map
	$(REMOVE) *.sym
	$(REMOVE) *.lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(OBJ:.o=.s)
	$(REMOVE) .dep/*
	$(REMOVEDIR) .dep
	$(REMOVE) ../../hexout/'$(TARGET)$(VERSEP)'*.hex

program:
	avrdude -c avrisp2 -p $(MCU) -B 0.5 -P usb -v -y -U flash:w:$(TARGET).hex
#	$(COPY) ryba.hex g:/mrtp/
#	$(COPY) $(TARGET).hex g:/mrtp/ryba.hex
#	$(COPY) $(TARGET).hex D:\P\HEX\main.hex
#	D:\P\HEX\avrosp -dATmega128 -ifmain.hex -pf -vf -e
#	protoss_avrosp -dATmega128 -ifmain.hex -pf -vf -e
#	!prog32.bat

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex eep lss sym coff extcoff \
clean clean_list program debug gdb-config

