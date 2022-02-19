PROJECT=stm32f4_uart
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy
LD=arm-none-eabi-ld
SF=st-flash
CPU= cortex-m4

HEX=$(PROJECT).hex
BIN=$(PROJECT).bin
ELF=$(PROJECT).elf


##################### CPU FLAGS #############################
#CPU_FLAGS  = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nosys.specs 
#CPU_FLAGS  += -static -Wl,-cref,-u,Reset_Handler 
#CPU_FLAGS  += -Wl,-Map=stm32f4_uart.map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -lc -lm 
#CPU_FLAGS  += -Wl,--end-group -specs=nano.specs 
CPU_FLAGS  = -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000  
#CPU_FLAGS  += -Tstm32f4_flash.ld -specs=nosys.specs  -g -O2 -Wall
#CPU_FLAGS +=   -mthumb -mcpu=cortex-m4  -mfloat-abi=hard -mfpu=fpv4-sp-d16 
#############################################################

######################### VARIABLES #########################
ROOT=$(PWD)
SRC_PATH = $(ROOT)/src
LIB_PATH = $(ROOT)/lib
LIB_SRC_PATH=$(LIB_PATH)/src/periph
INC_PATH = $(ROOT)/lib/inc

#############################################################

######################### FLAGS #############################
SRC = $(wildcard $(SRC_PATH)/*.c) 
SRC += $(wildcard $(SRC_PATH)/*.s) 
SRC += $(wildcard $(LIB_SRC_PATH)/*.c) 
OBJS_O=$(SRC:.c=.o)
OBJS=$(OBJS_O:.s=.o)

LIB = 	-L $(LIB_PATH) 
		
INC = 	-I $(INC_PATH)/core/ \
		-I $(SRC_PATH) \
		-I $(INC_PATH)/periph/ \
		-I $(INC_PATH)/device/ \
		-I /usr/lib/arm-none-eabi/include

C_FLAGS =	$(CPU_FLAGS) -mthumb -mcpu=cortex-m4 

LD_FLAGS = -T stm32f4_flash.ld -mthumb -mcpu=cortex-m4  --specs=nosys.specs 
#############################################################

all:$(HEX)  $(BIN)

$(HEX):$(ELF)
	@echo "[MAKE]$@ derleniyor"
	$(OBJCOPY) -O ihex $^ $@

$(BIN):$(ELF)
	@echo "[MAKE]$@ derleniyor"
	$(OBJCOPY) -O binary $^ $@

$(ELF):$(OBJS)
	@echo "[MAKE]$@ derleniyor"
	$(CC) $(INC) $(LIB)  $(LD_FLAGS) -o $@ $^ 

$(SRC_PATH)/%.o:$(SRC_PATH)/%.s
	@echo "[MAKE]$@ derleniyor"
	$(CC) -c $(C_FLAGS) $< -o $@

$(SRC_PATH)/%.o:$(SRC_PATH)/%.c
	@echo "[MAKE]$@ derleniyor"
	$(CC) $(C_FLAGS) $(INC)  -c $^ -o $@
#	$(CC) -MM $(C_FLAGS)  $(INC)   $< > $*.d

$(LIB_SRC_PATH)/%.o:$(LIB_SRC_PATH)/%.c
	@echo "[MAKE]$@ derleniyor"
	$(CC) $(C_FLAGS) $(INC)  -c $(@:.o=.c) -o $@


clean:	
	rm -f $(BIN) 
	rm -f  $(HEX) 
	rm -f $(ELF) 
	rm -f  $(SRC_PATH)/*.o
	rm -f $(LIB_SRC_PATH)/*.o

upload:
	$(SF) write $(HEX) 0x08000000

delete:
	$(SF) erase

debug: $(ELF)
	st-util $(ELF)