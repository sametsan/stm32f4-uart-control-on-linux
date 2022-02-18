CC = arm-none-eabi-gcc 

FLAGS =  -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000  

INCLUDE = -Ilib/inc/periph/ -Ilib/inc/device -Ilib/inc/core 

SOURCE = src/main.c lib/src/periph/stm32f4xx_gpio.c lib/src/periph/stm32f4xx_rcc.c

TARGET = main.bin

all : 

	$(CC) --specs=nosys.specs $(FLAGS) $(INCLUDE) $(SOURCE) -o $(TARGET) 


clean:	
	rm $(TARGET) 

upload:
	st-flash write $(TARGET)  0x08000000 

delete:
	st-flash erase