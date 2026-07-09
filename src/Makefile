PATCH_BIN = build/infection.patch
EE_BIN = infection.elf
EE_OBJS = infection.o
EE_LINKFILE := linkfile

all: $(PATCH_BIN) 

clean:
	rm -f $(PATCH_BIN) $(EE_BIN) $(EE_OBJS)


include $(PS2SDK)/samples/Makefile.pref


# Include directories
EE_INCS := -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I. $(EE_INCS)

# Optimization compiler flags
EE_OPTFLAGS ?= -O2

# Warning compiler flags
EE_WARNFLAGS ?= -Wall

# Debug information flags
EE_DBGINFOFLAGS ?= -gdwarf-2 -gz

# C compiler flags
EE_CFLAGS := -D_EE -G0 $(EE_OPTFLAGS) $(EE_WARNFLAGS) $(EE_DBGINFOFLAGS) $(EE_CFLAGS)

# Linker flags
EE_LDFLAGS := -L$(PS2SDK)/ee/lib -Wl,-eentry -Wl,-zmax-page-size=128 -nodefaultlibs -nolibc -nostdlib

# Assembler flags
EE_ASFLAGS := -G0 $(EE_ASFLAGS)

# Command for ensuring the output directory for the rule exists.
DIR_GUARD = @$(MKDIR) -p $(@D)

%.o: %.c
	$(DIR_GUARD)
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

%.o: %.S
	$(DIR_GUARD)
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

%.o: %.s
	$(DIR_GUARD)
	$(EE_AS) $(EE_ASFLAGS) $< -o $@

$(EE_BIN): $(EE_OBJS)
	$(DIR_GUARD)
	$(EE_CC) -T$(EE_LINKFILE) $(EE_OPTFLAGS) -o $@ $(EE_OBJS) $(EE_LDFLAGS)
#    $(EE_STRIP) --strip-unneeded -R .mdebug.eabi64 -R .reginfo -R .comment $@

$(PATCH_BIN): $(EE_BIN)
	$(DIR_GUARD)
	python3 patcher.py