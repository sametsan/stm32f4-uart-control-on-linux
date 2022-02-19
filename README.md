# stm32f4-uart-control-on-linux


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

# Debug için

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

