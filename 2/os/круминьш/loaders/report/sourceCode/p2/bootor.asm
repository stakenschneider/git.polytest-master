; Загрузочный сектор должен был загрузить нас
; по адресу 0:0x1000. 

BOOTOR_MAGIC equ 0x12EF	; Сигнатура

org	0x1000
base:

; Определимся с регистрами:
	xor	ax, ax
	mov	es, ax
	mov	ds, ax
	mov	ss, ax
	mov	sp, 0x1000

; Установим видеорежим, очиститься экран
	mov	ax, 3
	int	10h

; Вообщим о том что мы загрузились
	cmp	word [BOOTOR_SIG], BOOTOR_MAGIC
	je	near GoodSig

; Загрузочный сектор неправильно нас загрузил
	mov	si, mFAIL
	call	print
	mov	si, mBadSig
	call	print

die:	jmp	short die

mBadSig	db 'Major problem: Loader did not load kernel completely.',10,13
	db 'Reboot computer',10,13,0
mOK	db '[ OK ]',10,13,0
mFAIL	db '[FAIL]',10,13,0
mHello	db 'Hello from bootor',10,13,0


; -----------------------------------------------------
print:
	cld
	pusha
.PrintChar:
	lodsb
	test	al, al
	jz	short .Exit
	mov	ah, 0eh
	mov	bl, 7
	int	10h
	jmp	short .PrintChar
.Exit:
	popa
	ret
; -----------------------------------------------------

GoodSig:	mov	si, mOK
	call	print
	
	mov	si, mHello
	call	print
	
	jmp	die
	
; -----------------------------------------------------
BOOTOR_SIG dw BOOTOR_MAGIC
align	16