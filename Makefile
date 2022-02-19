CC = arm-none-eabi-gcc 


LD_FLAGS = -T stm32f4_flash.ld -mthumb -mcpu=cortex-m4  --specs=nosys.specs 
CPU_FLAGS =  -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000  
C_FLAGS =	 -mthumb -mcpu=cortex-m4 
FLAGS= $(CPU_FLAGS) $(LD_FLAGS) $(C_FLAGS)




INCLUDE = -Ilib/inc/periph/ -Ilib/inc/device -Ilib/inc/core 

SOURCE = src/*.c lib/src/periph/*.c 

TARGET = main.bin

all : 

	$(CC)  $(FLAGS) $(INCLUDE) $(SOURCE) -o $(TARGET) 


clean:	
	rm $(TARGET) 

upload:
	st-flash write $(TARGET)  0x08000000 

delete:
	st-flash erase