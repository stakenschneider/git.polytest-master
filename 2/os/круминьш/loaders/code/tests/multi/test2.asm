[BITS 16]
[ORG 0x7C00]

jmp	short	start ; Переход к исполняемому коду
nop

%include "fatTable.asm"

start:
	cld	; Отключение прерываний
	
	; Печать пользователю сообщения с выбором ядра
	mov si, SelectMessage	;Записываем в стек указатель на строку
  call PrintString	;Вызов процедуры печати строки
	
	; Считывание клавиши
	mov ah, 10h
	int 16h
	mov ah, 00h
  mov bx, si ; сохраняем указатель на стек в bx
	pusha

  
	
	; Сравниваем считанный символ
	cmp al,'1'
	je select_first
	cmp al,'2'
	je select_second

; В противном случае выводим сообщение об ошибке
  mov si, SelectErrorMessage	;Записываем в стек указатель на строку с сообщением об ошибке
  call PrintString ; Выводим строку
  int 18h ; Прерывание, сигнализирующее о неудачной загрузке

; Если выбран первый исполняемый файл
select_first:
  mov si, ProgramName1 ; переносим указатель стека на строку с именем первого файла
  jmp write_name ; переходим к копированию имени

; Если выбран второй исполняемый файл
select_second:
	mov si, ProgramName2 ; переносим указатель стека на строку с именем второго файла
	
write_name:
  mov di, ProgramName ; Записываем в di адрес, куда будет записано имя запускаемой программы
	mov cx, 11 ; записываем в cx длинну имени
write_char:
  mov ax, [si] ; берем первый символ из имени программы
	mov [di], ax ; записываем ее в область памяти для запускаемой программы
	inc si ; увеличиваем si 
	inc di ; и di для перехода к следующему символу
	dec cx ; уменьшаем счетчик
	jnz write_char ; если не ноль, то переходим к копированию следующего символа
	mov si, bx ; восстанавливаем указатель на стек
	popa
	
  push cs
  pop ds
  mov [var_logical_drive_number], dl ; сохранение номера загрузочного диска BIOS
  and byte [var_cluster_number+3], 0Fh ; маскировка значения кластера 
  mov esi, [var_cluster_number] ; Записываем в esi номер кластера корневой директории	

; Чтение корневой директории
RootDirReadContinue:
  push 60h ; 60h - смещение загрузочного образа BIOS
  pop es ; Достаем значение из стека и помещаем его в es
  xor bx, bx ; Обнуление bx
  call ReadCluster ; Вызов функции чтения одного кластера из корневой директории
  push esi ; сохранение номера следующего кластера в esi
  pushf ; Записываем флаг в стек

; Поиск и запуск исполняемого файла
  push 60h
  pop  es ; Достаем значение из стека и помещаем его в es
  xor  di, di ; Обнуляем di
  mov  si, ProgramName ; Записываем в стек имя программы для запуска
       
  mov al, [var_sector_by_claster] ; Записываем в al количество секторов в кластере
  cbw ; Преобразуем содержимое al в знаковое слово (номер) в ax 
  mul word [var_byte_per_sector]; Умножаем количество секторов в кластере на количество байт в секторе и получаем количество байт в кластере
  shr ax, 5 ; Сдвиг вправо регистра ax на 5 бит и получаем количество записей каталога
  mov dx, ax ; Записываем содержимое в регистр dx

; Поиск имени файла
; В стек помещено имя файла
; dx - количество точек входа
; в результате в esi будет записан номер кластера
FindName:
  mov cx, 11 ; Записываем в cx длину имени (11 байт)

; Цикл поиска файла
FindNameCycle:
  cmp byte [es:di], ch ; Сравниваем байты текущей записи с тем, что нужно найти
  jne FindNameNotEnd ; Если не равны, то продолжаем искать
  jmp ErrFind ; Если конец корневой директории (найдена NULL запись) то выводим сообщение об ошибке

; Продолжение поиска файла
FindNameNotEnd:
  pusha ; сохраняем в стеке содержимое регистров AX, CX, DX, BX, SP, BP, SI, DI
  repe cmpsb ; Сравниваем строки
  popa ; Восстанавливаем содержимое регистров AX, CX, DX, BX, SP, BP, SI, DI
  je FindNameFound ; Если равны, то файл найден и переходим по метке FindNameFound
  add di, 32 ; Прибавляем к di 32 (переход к следующей записи)
  dec dx ; Уменьшаем счетчик
  jnz FindNameCycle	; Повторяем итерацию для новой записи
  popf	; Восстанавливаем флаги
  pop esi	; В esi записывается адрес следующего кластера корневой директории
  jc RootDirReadContinue ; Если остались кластеры, то начинаем анализ следующего кластера
  jmp ErrFind ; Файл не найден, выводим сообщение об ошибке

; Имя файла найдено
FindNameFound:
  push word [es:di+14h]
  push word [es:di+1Ah]
  pop esi	; Записываем номер кластера в si

; Загрузка файла
  push 60h
  pop es
  xor bx, bx

; Цикл поиска файла
FileReadContinue:
  call ReadCluster ; чтение одного кластера в корневой директории
  jc FileReadContinue ; Если не считали все, то продолжаем чтение

; Запуск исполняемой программы
  push 60h
  pop ds ; записываем в ds значение 60h
  mov ax, ds ; В ax и ds номер сегмента, куда будет загружен исполняемый файл
       
  sub ax, 10h 
  mov es, ax
  mov ds, ax
  mov ss, ax
  xor sp, sp ; Очистка стека
  push es
  push word 100h ; Записываем в стек адрес, по которому будет загружен файл
  mov  dl, [cs:var_logical_drive_number] 
  retf

; Функция чтения кластера
ReadCluster:
  mov ax, [var_byte_per_sector]
  shr ax, 2	; Помещаем в ax количество записей в секторе
  cwde
  mov ebp, esi	; Записываем в ebp номер кластера
  xchg  eax, esi ; Меняем значения в eax и esi
  cdq
  div esi	; В eax записан номер сектора
  movzx edi, word [var_reserved_sector_counter] ; Записываем в edi количество зарезервированных секторов
  add edi, [var_number_of_hidden_sectors] ; Прибавляем к этому количество спрятанных секторов
  add eax, edi	; Прибавляем номер сектора

  push dx	; Записываем в стек dx (номер сектора)
  mov cx, 1
  call ReadSector	; Функция чтения одного сектора

  pop si	; Выкидываем ненужную запись из si. Теперь на вершине стека номер сектора внутри кластера
  add si, si ; Увеличиваем si в 4 раза
  add si, si ; что бы получить маску следующего кластера
  and byte [es:si+3], 0Fh	; маска значения кластера
  mov esi, [es:si]	; В esi записываем номер следующего кластера

  lea eax, [ebp-2]
  movzx ecx, byte [var_sector_by_claster] ; Записываем в ecx количество секторов в кластере
  mul ecx ; Возводим в квадрат
  mov ebp, eax ; Записываем в ebp остаток

  movzx eax, byte [var_num_fat_copies] ; Записываем в ax количество копий
  mul dword [var_number_of_sectors_per_fat] ; Умножаем на количество секторов в FAT-таблице
      
  add eax, ebp ; прибавляем остаток от возведения в квадрат
  add eax, edi ; Получаем адрес нужного сектора
      
  call ReadSector
        
  mov ax, [var_byte_per_sector] ; Записываем в ax количество байт в секторе
  shr ax, 4 ; Записываем ax количество слов в секторе (сдвиг враво на 4)
  mul cx ; умножаем на количество секторов (записан в cx после функции ReadSector)
      
  mov cx, es ; записываем в cx номер текущего кластера
  add cx, ax ; получаем номер следующего кластера, прибавив к номеру текущег кластера размер текущего кластера
  mov es, cx ; Запись в es:bx номер следующего кластера
      
  cmp esi, 0FFFFFF8h ; Если последний кластер, то перенос будет равен 0, иначе 1
  ret 

; Чтение сектора
ReadSector:
  pushad ; сохраняем регистры общего назначения в стек

; Чтение следующего сектора
ReadSectorNext:
  pusha ; Сохраняем регистры в стеке
	
; Запись команд в стек
  push byte 0 ; записываем в стек 0
  push byte 0 ; записываем в стек 0
  push eax ; записываем в стек 1 для регулирования LBA
  push es ; записываем в стек es
  push bx ; записываем в стек смещение
  push byte 1 ; слово счетчика 1 сектор
  push byte 16 ; размер пакета 16 байт, зарезервированныx 0 байт
       
  mov ah, 42h
  mov dl, [var_logical_drive_number] ; Записываем в dl номер устройства
  mov si, sp ; записываем в si указатель стека
  push ss ; записываем в стек ss
  pop ds ; записываем значение ss в регистр ds
  int 13h ; прерывание дискового ввода - вывода
  push cs ; запись значения в регистре cs
  pop ds ; в регистр ds
       
  jc short ErrRead
  add  sp, 16 ; две команды меняются местами чтобы не перезаписать флаг переноса
       
  popa ; Восстанавливаем регистры
  dec cx ; Уменьшаем счетчик
  jz ReadSectorDone ; Последний сектор
       
  add  bx, [var_byte_per_sector] ; регулирование смещения для следующего сектора
  add  eax, byte 1 ; регулирование LBA для следующего сектора
  jmp  short ReadSectorNext ; Читаем следующий сектор

ReadSectorDone:
  popad ; сохраняем регистры в стеке
  ret

PrintString:	;Процедура печати строки
	mov ax, si ; сохраняем адрес стека
next_character:
	mov al, [si]	;Берем один байт из строки и записываем его в регистр AL
	inc si	;Увеличиваем указатель SI
	or al, al	;Проверка конца строки
	jz exit_function
	call PrintCharacter ;Печатаем символ
	jmp next_character
exit_function:
	mov si, ax ; восстанавливаем стек
  ret

PrintCharacter:	;Процедура печати символа
	mov ah, 0x0E	;Флаг того, что нам нужно вывести на экран один символ
	mov bh, 0x00	;Номер страницы
	mov bl, 0x07	;Флаг того, что выводится светлый текст на черном фоне

	int 0x10	;Вызов прерывания видео
	ret	;Возращение к вызванной процедуре
	
; Сообщение об ошибке

ErrRead:
ErrFind:
  mov si, ErrorMessage	;Записываем в стек указатель на строку
  call PrintString
exit_err:
 jmp short $

SelectMessage db "1.FirstSelection.BIN", 13,10, "2.SecondSelection.BIN", 13, 10, 0
ProgramName1	db	"FirstSelection   BIN"   ; Имя исполняемой первой программы
ProgramName2	db	"SecondSelection   BIN"   ; Имя исполняемой второй программы
ProgramName	db	"NNNNN   BIN"   ; Имя исполняемой программы
ErrorMessage db "ERROR", 13, 10, 0
SelectErrorMessage db "SELECT ERROR", 13, 10, 0

times (1024-2-($-$$)) db 0 ; Заполняем оставшееся пространство нулями
		
dw	0AA55h ; Сигнатура загрузчика
