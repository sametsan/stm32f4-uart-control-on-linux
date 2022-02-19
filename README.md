# stm32f4-uart-control-on-linux

STM32F4 Discovery board üzerinde uart arayüzü ile led kontrolü sağlar. 

echo modu,led yanık kalma ve sönük kalma süresi ayarlanabilir. 

UART üzerinden kullanılabilen bazı komutlar şöyledir;

echo modunu aktif etmek için;
```
    start 
```

echo modunu pasif etmek için;
```
    stop 
```

Led aktif süresini ayarlamak  için;
```
    ledon=TIME_ms 
```

Led pasif süresini ayarlamak  için;
```
    ledoff=TIME_ms 
```

## Kurulum


###  Derleme için 
```console
    make 
```

###  Board yükleme için
```console
    make upload
```

###  Board belleğini temizlemek için
```console
    make delete
```

###  Derleme dosyalarını temizlemek için
```console
    make clean
```

###  Debug mod için
```console
    make debug
```

###  Debug için GDB bağlantısı
```console
    gdb
    target extended-remote localhost:4242
    load stm32f4_uart.elf
```

GDB kullanımı için : 
```console
    man gdb
```
