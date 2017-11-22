PROJECT         :=  myos
SOURCE_ROOT     :=  .
BUILD_DIR       :=  build

INCLUDE_DIR     :=
SOURCE_DIR      :=  $(SOURCE_ROOT)
SOURCE_EXCLUDE  :=  $(SOURCE_ROOT)/iso

OBJECT_ROOT     :=  $(BUILD_DIR)/obj
BUILD           :=  $(BUILD_DIR)/$(PROJECT).elf
LDS             :=  link.ld

find             =  $(filter-out $(SOURCE_EXCLUDE),$(wildcard $1/$2)) \
                    $(foreach dir,$(filter-out $(SOURCE_EXCLUDE),$(wildcard $1/*)),$(call find,$(dir),$2))
SOURCE_C        :=  $(foreach dir,$(SOURCE_DIR),$(call find,$(dir),*.c))
SOURCE_S        :=  $(foreach dir,$(SOURCE_DIR),$(call find,$(dir),*.asm))
OBJECT          :=  $(patsubst $(SOURCE_ROOT)%,$(OBJECT_ROOT)%,$(patsubst %.c,%.o,$(SOURCE_C))) \
                    $(patsubst $(SOURCE_ROOT)%,$(OBJECT_ROOT)%,$(patsubst %.asm,%_asm.o,$(SOURCE_S)))

LD              :=  ld
LDFLAGS         :=  -m elf_i386 -T $(LDS)
AS              :=  nasm
SFLAGS          :=  -f elf32
CC              :=  gcc
CFLAGS          :=  $(INCLUDE_DIR) -c -m32 -fno-stack-protector

.PHONY: clean

all: $(BUILD)

$(BUILD): $(OBJECT)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $(BUILD) $(OBJECT)

$(OBJECT_ROOT)/%_asm.o: $(SOURCE_ROOT)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(SFLAGS) -o $@ $<

$(OBJECT_ROOT)/%.o: $(SOURCE_ROOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BUILD) $(OBJECT)
