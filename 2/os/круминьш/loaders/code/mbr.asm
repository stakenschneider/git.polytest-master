section .text
     use16
     org  0x7C00  ; наша программа загружается по адресу 0x7C00
start:
     mov  ax, cs
     mov  ds, ax ; выбираем сегмент данных
 
     mov  si, message
     cld ; направление для строковых команд
     mov  ah, 0x0E  ; номер функции BIOS
     mov  bh, 0x00 ; страница видеопамяти
puts_loop:
     lodsb ; загружаем очередной символ в al
     test al, al ; нулевой символ означает конец строки
     jz   puts_loop_exit
     int  0x10 ; вызываем функцию BIOS
     jmp  puts_loop
puts_loop_exit:
     jmp  $ ; вечный цикл
 
message:
     db   'Hello World!',0
finish:
     times 0x1FE-finish+start db 0
     db   0x55, 0xAA ; сигнатура загрузочного сектора