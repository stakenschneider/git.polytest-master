; Общая часть для всех типов FAT
BS_jmpBoot:
jmp	short BootStart	; Переходим на код загрузчика
nop
BS_OEMName	db '*-v4VIHC'	; 8 байт, что было на моей дискете, то и написал
BPB_BytsPerSec	dw 0x200	; Байт на сектор
BPB_SecPerClus	db 1	; Секторов на кластер
BPB_RsvdSecCnt	dw 1	; Число резервных секторов
BPB_NumFATs	db 2	; Количектво копий FAT
BPB_RootEntCnt	dw 224	; Элементов в корневом катологе (max)
BPB_TotSec16	dw 2880	; Всего секторов или 0
BPB_Media	db 0xF0	; код типа устройства
BPB_FATsz16	dw 9	; Секторов на элемент таблицы FAT
BPB_SecPerTrk	dw 18	; Секторов на дорожку
BPB_NumHeads	dw 2	; Число головок
BPB_HiddSec	dd 0	; Скрытых секторов
BPB_TotSec32	dd 0	; Всего секторов или 0

; Заголовок для FAT12 и FAT16
BS_DrvNum	db 0	; Номер дика для прерывания int 0x13
BS_ResNT	db 0	; Зарезервировано для Windows NT
BS_BootSig	db 29h	; Сигнатура расширения
BS_VolID	dd 2a876CE1h	; Серийный номер тома
BS_VolLab	db 'X boot disk'	; 11 байт, метка тома
BS_FilSysType	db 'FAT12   '	; 8 байт, тип ФС
; Структура элемента каталога
struc	DirItem
	DIR_Name:	resb 11
	DIR_Attr:	resb 1
	DIR_ResNT:	resb 1
	DIR_CrtTimeTenth	resb 1
	DIR_CrtTime:	resw 1
	DIR_CrtDate:	resw 1
	DIR_LstAccDate:	resw 1
	DIR_FstClusHi:	resw 1
	DIR_WrtTime:	resw 1
	DIR_WrtDate:	resw 1
	DIR_FstClusLow:	resw 1
	DIR_FileSize:	resd 1
endstruc ;DirItem

; Наши не инициализированные переменные
; При инициализации они затрут не нужные нам поля заголовка FAT: BS_jmpBoot и ;BS_OEMName
struc	NotInitData
	SysSize:	resd 1	; Размер системной области FAT
	fails:	resd 1	; Число неудачных попыток при чтении
	fat:	resd 1	; Номер загруженного сектора с элементами FAT
endstruc ;NotInitData


; По этому адресу мы будем загружать загрузчик
%define SETUP_ADDR	0x1000
; А по этому адресу нас должны были загрузить
%define BOOT_ADDR	0x7C00
%define BUF	0x500

BootStart:
	cld
	xor	cx, cx
	mov	ss, cx
	mov	es, cx
	mov	ds, cx
	mov	sp, BOOT_ADDR
	mov	bp, sp
	; Сообщим о том что мы загружаемся
	mov	si, BOOT_ADDR + mLoading
	call	print

	mov	al, [byte bp+BPB_NumFATs]
	cbw
	mul	word [byte bp+BPB_FATsz16]
	add	ax, [byte bp+BPB_HiddSec]
	adc	dx, [byte bp+BPB_HiddSec+2]
	add	ax, [byte bp+BPB_RsvdSecCnt]
	adc	dx, cx
	mov	si, [byte bp+BPB_RootEntCnt]
	; dx:ax - Номер первого сектора корневого каталога
	; si - Количество элементов в корневом каталоге
	pusha
	; Вычислим размер системной области FAT = резервные сектора +
	; все копии FAT + корневой каталог
	mov	[bp+SysSize], ax	; осталось добавить размер каталога
	mov	[bp+SysSize+2], dx
	; Вычислим размер корневого каталога
	mov	ax, 32
	mul	si
	; dx:ax - размер корневого каталога в байтах, а надо в секторах
	mov	bx, [byte bp+BPB_BytsPerSec]
	add	ax, bx
	dec	ax
	div	bx
	; ax - размер корневого каталога в секторах
	add	[bp+SysSize], ax	; Теперь мы знаем размер системной
	adc	[bp+SysSize+2], cx	; области FAT, и начало области данных
	popa
	; В dx:ax - снова номер первого сектора корневого каталога
	; si - количество элементов в корневом каталоге


NextDirSector:
	; Загрузим очередной сектор каталога во временный буфер
	mov	bx, 700h	; es:bx - буфер для считываемого сектора
	mov	di, bx	; указатель текущего элемента каталога
	mov	cx, 1	; количество секторов для чтения
	call	ReadSectors
	jc	near DiskError	; ошибка при чтении

RootDirLoop:
	; Ищем наш файл
	; cx = 0 после функции ReadSectors
	cmp	[di], ch	; byte ptr [di] = 0?
	jz	near NotFound	; Да, это последний элемент в каталоге
	; Нет, не последний, сравним имя файла
	pusha
	mov	cl, 11	; длина имени файла с расширением
	mov	si, BOOT_ADDR + LoaderName	; указатель на имя искомого файла
	rep	cmpsb	; сравниваем
	popa
	jz	short Found	; Нашли, выходим из цикла
	; Нет, ищем дальше
	dec	si	; RootEntCnt
	jz	near NotFound	; Это был последний элемент каталога
	add	di, 32	; Переходим к следующему элементу каталога
	; bx указывает на конец прочтенного сектора после call ReadSectors
	cmp	di, bx	; Последний элемент в буфере?
	jb	short RootDirLoop	; Нет, проверим следующий элемент
	jmp	short NextDirSector	; Да последний, загрузим следующий сектор

Found:
	; Загрузка загрузчика
	mov	bx, SETUP_ADDR
	mov	ax, [byte di+DIR_FstClusLow]	; Номер первого кластера файла
	; Загружаем сектор с элемнтами FAT, среди которых есть FAT[ax]
	; LoadFAT сохраняет значения всех регистров
	call	LoadFAT

ReadCluster:
	; ax - Номер очередного кластера
	; Загрузим его в память
	push	ax
	; Первые два элемента FAT служебные
	dec	ax
	dec	ax
	; Число секторов для чтения
	; cx = 0 после ReadSectors
	mov	cl, [byte bp+BPB_SecPerClus]	; Секторов на кластер
	mul	cx
	; dx:ax - Смещение кластера относительно области данных
	add	ax, [byte bp+SysSize]
	adc	dx, [byte bp+SysSize+2]
	; dx:ax - Номер первого сектора требуемого кластера
	; cx еще хранит количество секторов на кластер
	; es:bx - конец прошлого кластера и начало нового
	call	ReadSectors	; читаем кластер
	jc	near DiskError	; Увы, ошибка чтения
	pop	ax	; Номер кластера
	; Это конец файла?
	; Получим значение следующего элемента FAT
	pusha
	; Вычислим адрес элемента FAT
	mov	bx, ax
	shl	ax, 1
	add	ax, bx
	shr	ax, 1
	; Получим номер сектора, в котором находится текущий элемент FAT
	cwd
	div	word [byte bp+BPB_BytsPerSec]
	cmp	ax, [bp+fat]	; Мы уже читали этот сектор?
	popa
	je	Checked	; Да, читали
	; Нет, надо загрузить этот сектор
	call	LoadFAT


Checked:
	; Вычислим адрес элемента FAT в буфере
	push	bx
	mov	bx, ax
	shl	bx, 1
	add	bx, ax
	shr	bx, 1
	and	bx, 511	; остаток от деления на 512
	mov	bx, [bx+0x700]	; а вот и адрес
	; Извлечем следующий элемент FAT
	; В FAT16 и FAT32 все немного проще :(
	test	al, 1
	jnz	odd
	and	bx, 0xFFF
	jmp	short done

odd:
	shr	bx, 4

done:
	mov	ax, bx
	pop	bx
	; bx - новый элемент FAT
	cmp	ax, 0xFF8	; EOF - конец файла?
	jb	ReadCluster	; Нет, читаем следующий кластер
	; Наконец-то загрузили
	mov	ax, SETUP_ADDR>>4	; SETUP_SEG
	mov	es, ax
	mov	ds, ax
	; Передаем управление, наше дело сделано :)
	jmp	SETUP_ADDR>>4:0
	
LoadFAT	;proc
; Процедура для загрузки сектора с элементами FAT
; Элемент ax должен находится в этом секторе
; Процедура не должна менять никаких регистров
	pusha
	; Вычисляем адрес слова содержащего нужный элемент
	mov	bx, ax
	shl	ax, 1
	add	ax, bx
	shr	ax, 1
	cwd
	div	word [byte bp+BPB_BytsPerSec]
	; ax - смещение сектора относительно начала таблицы FAT
	mov	[bp+fat], ax	; Запомним это смещение, dx = 0
	cwd			; dx:ax - номер сектора, содержащего FAT[?]
	; Добавим смещение к первой копии таблицы FAT
	add	ax, [byte bp+BPB_RsvdSecCnt]
	adc	dx, 0
	add	ax, [byte bp+BPB_HiddSec]
	adc	dx, [byte bp+BPB_HiddSec+2]
	mov	cx, 1	; Читаем один сектор. Можно было бы и больше, но не быстрее
	mov	bx, 700h	; Адрес буфера
	call	ReadSectors
	jc	DiskError	; Ошибочка вышла
	popa
	ret

; *************************************************
; *          Чтение секторов с диска              *
; *************************************************
; * Входные параметры:                            *
; * dx:ax       - (LBA) номер сектора             *
; * cx          - количество секторов для чтения  *
; * es:bx       - адрес буфера                    *
; *************************************************
; * Выходные параметры:                           *
; * cx       - Количество не прочтенных секторов  *
; * es:bx    - Указывает на конец буфера          *
; * cf = 1   - Произошла ошибка при чтении        *
; *************************************************

ReadSectors	;proc
next_sector:
	; Читаем очередной сектор
	mov	byte [bp+fails], 3	; Количество попыток прочесть сектор

try:
	; Очередная попытка
	pusha
	; Преобразуем линейный адрес в CSH
	; dx:ax = a1:a0
	xchg	ax, cx		; cx = a0
	mov	ax, [byte bp+BPB_SecPerTrk]
	xchg	ax, si		; si = Scnt
	xchg	ax, dx		; ax = a1
	xor	dx, dx
	; dx:ax = 0:a1
	div	si		; ax = q1, dx = c1
	xchg	ax, cx		; cx = q1, ax = a0
	; dx:ax = c1:a0
	div	si		; ax = q2, dx = c2 = c
	inc	dx		; dx = Sector?
	xchg	cx, dx		; cx = c, dx = q1
	; dx:ax = q1:q2
	div	word [byte bp+BPB_NumHeads]	; ax = C (track), dx = H
	mov	dh, dl		; dh = H
	mov	ch, al
	ror	ah, 2
	or	cl, ah
	mov	ax, 0201h		; ah=2 - номер функции, al = 1 сектор
	mov	dl, [byte bp+BS_DrvNum]
	int	13h
	popa
	jc	Failure	; Ошибка при чтении
	; Номер следующего сектора
	inc	ax
	jnz	next
	inc	dx

next:
	add	bx, [byte bp+BPB_BytsPerSec]
	dec	cx	; Все сектора прочтены?
	jnz	next_sector	; Нет, читаем дальше

return:
	ret

Failure:
	dec	byte [bp+fails]	; Последняя попытка?
	jnz	try	; Нет, еще раз
	; Последняя, выходим с ошибкой
	stc
	ret
;ReadSectors	endp



; Сообщения об ошибках
NotFound:	; Файл не найден
	mov	si, BOOT_ADDR + mLoaderNotFound
	call	print
	jmp	short die

DiskError:	; Ошибка чтения
	mov	si, BOOT_ADDR + mDiskError
	call	print
	;jmp	short die	

die:	; Просто ошибка
	mov	si, BOOT_ADDR + mReboot
	call	print

_die:	; Бесконечный цикл, пользователь сам нажмет Reset
	jmp	short _die
; Процедура вывода ASCIIZ строки на экран
; ds:si - адрес строки

print:	; proc
	pusha
print_char:
	lodsb	; Читаем очередной символ
	test	al, al	; 0 - конец?
	jz	short pr_exit	; Да конец
	; Нет, выводим этот символ
	mov	ah, 0eh
	mov	bl, 7
	int	10h
	jmp	short print_char	; Следующий
pr_exit:
	popa
	ret

%define	endl 10,13,0

; Строковые сообщения
mLoading	db 'Loading...',endl
mDiskError	db 'Disk I/O error',endl
mLoaderNotFound	db 'Loader not found',endl
mReboot		db 'Reboot system',endl

; Выравнивание размера образа на 512 байт
times 499-($-$$) db 0
LoaderName	db 'BOOTOR     '	; Имя файла загрузчика
BootMagic	dw 0xAA55	; Сигнатура загрузочного сектора