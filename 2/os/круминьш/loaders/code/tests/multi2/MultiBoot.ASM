;ðåãèñòð dl cîäåðæèò íîìåð çàãðóçî÷íîãî äèñêà!

use16
;======== Êîïèðóåì òóøó çàãðóç÷èêà ïî àäðåñó 0000:0600h ===================
    mov ax, 7C0h	;ïî ýòîìó àäðåñó ìû çàãðóæåíû
    mov ds, ax	;íàñòðàèâàåì ðåãèñòðû - ñòåê, ñåãìåíòû è ò .ï.
    xor si, si

    mov ax, 60h	;ïî ýòîìó àäðåñó êîïèðóåìñÿ
    mov es, ax
    xor di, di

    mov cx, 0FFh 	;ñêîëüêî áàéò êîïèðîâàòü

    rep movsw	;êîïèðóåì

    jmp 0000:0618h    ;Ïåðåäàåì óïðàâëåíèå íà íîâîå ðàñïîëîæåíèå êîäà - ñëåäóþùàÿ çà jmp èíñòðóêöèÿ

;======== Ïðèâåòñòâóåì ïîëüçîâàòåëÿ ===================================
	  mov ax, hello_msg_1
	  call print
	  mov ax, hello_msg_2
	  call print

;======== Ïðîâåðÿåì òàáëèöó ðàçäåëîâ ===================================
	  mov si, [part_adr]   ; íà÷àëî òàáëèöû ðàçäåëîâ
	  mov bh, 80h	; çàãðóçî÷íûé ðàçäåë  - ïðèçíàê

	  mov cl, -1	; íàñòðîéêà ñ÷åò÷èêà ðàçäåëîâ
partitions_chek:
	  cmp cl, 3			   ;åñëè óæå áûëî ïðîâåðåíî 4 çàïèñè, âûõîäèì èç öèêëà è ïåðåõîäèì ê îáðàáîòêå çàïèñåé
	  je partition_select

	  add si, 10h		   ; íàñòðàèâàåì íà àäðåñ ñëåäóþùåé çàïèñè òàáëèöû
	  inc cl			   ; óâåëè÷èâàåì ÷èñëî îáðàáîòàííûõ çàïèñåé

	  mov bl, [es:si]	                  ; ñìîòðèì íà ïðèçíàê ðàçäåëà
	  cmp bl, bh
	  jne partitions_chek		   ;çàïèñü íå ÿâëÿåòñÿ çàãðóçî÷íîé

	  call partitions_process	   ;çàïèñü çàãðóçî÷íàÿ - âûâåäåì åå íîìåð è ïîÿñíÿþùåå ñîîáùåíèå
				   ;[es:si] ñîäåðæèò àäðåñ çàïèñè â òàáëèöå ðàçäåëîâ
				   ;cl - íîìåð ðàçäåëà

	  jmp partitions_chek	                  ; ïðîâåðÿåì åùå

;======== Ïîäïðîãðàììà âûâîäà èíîôðìàöèè îá àêòèâíîì ðàçäåëå =============================
partitions_process:
	  mov ax, boot_part_msg	;ïîÿñíÿþùåå ñîîáùåíèå
	  call print

	  mov di, part_num		;ïîðÿäêîâûé íîìåð ðàçäåëà îò 0 äî 3
	  add [ds:di], cl
	  mov ax, part_num
	  call print
	  sub [ds:di], cl

	  mov di, boot_flags
	  mov ch, 0
	  add di, cx
	  mov byte[ds:di], 1

	  ret;
;=======================================================================

partition_select:
	  ;Îáðàáàòûâàåì ïîëüçîâàòåëüñêèé ââîä ñ ïîìîùüþ ïðåðûâàíèÿ 16
	  mov ax, select_part_msg	;ïðîñüáà âûáðàòü ðàçäåë
	  call print

choise:   mov di, boot_flags		;íàñòðîéêà ðåãèñòðîâ äëÿ ïîëó÷åíèÿ ðåçóëüòàòà ââîäà
	  mov si, [part_adr]

	  mov ah, 0
	  int 16h			;æäåì ââîäà

p0:	  cmp al, 48		;ñðàâíèâàåì êîäû íàæàòîé êëàâèøè ñ 0, 1, 2 è 3 - îïðåäåëÿåì âûáðàííûé ðàçäåë
	  jne p1
	  add si, 10h
	  jmp disk

p1:	  cmp al, 49		;âûáðàí ïåðâûé ðàçäåë?
	  jne p2
	  add si, 20h
	  jmp disk

p2:	  cmp al, 50		;âûáðàí âòîðîé ðàçäåë?
	  jne p3
	  add si, 30h
	  jmp disk

p3:	  add si, 40h		;âûáðàí òðåòèé ðàçäåë?
	  cmp al, 51
	  je disk

wrong_choise:			;áûëà ââåäåíà åðóíäà
	  mov ax, wrong_input_msg	;ñîîáùàåì îá ýòîì è æäåì íîâîãî ââîäà
	  call print
	  jmp choise

disk:	  mov ah, 0
	  sub al, 48		      ; ñíà÷àëà ïðîâåðêà, âûáðàë ëè ïîëüçîâàòåëü äåéñòâèòåëüíî çàãðóçî÷íûé ðàçäåë
	  add di, ax
	  cmp byte [ds:di], 0
	  je wrong_choise
				      ; ïî [es:si] ñîäåðæèòñÿ çàïèñü òàáëèöû ðàçäåëîâ
				      ; î âûáðàííîì çàãðóçî÷íîì äèñêå

	  mov ah, 41h		      ; ïðîâåðêà ïîääåðæêè äèñêîì ðàñøèðåííîãî ðåæèìà (> 8 GB)
				      ; dl ñîäåðæèò íîìåð äèñêà
	  mov bx, 55AAh		      ;ïðîâåðÿåì ÷åðåç ïðåðûâàíèå
	  int 13h
	  jc  ext_not_present_error	      ;îøèáêà ïðè ÷òåíèè - âûâîäèì ñîîáùåíèå
	  shr  cx, 1			      ;ñ÷èòàëè îäèí ñåêòîð?
	  jnb  ext_not_present_error		
	  cmp  bx, 0AA55h		      ;âñå õîðîøî - áóäåì ãðóçèòü â íóæíóþ îáëàñòü ïàìÿòè
	  je   read_boot_sect

ext_not_present_error:		     ;îøèáêà ïðè ÷òåíèè äèñêà
	  mov ax, ext_not_pres_msg
	  call print
	  int 18h

read_boot_sect:
	  mov ah, 42h		;ïðîèçâîäèì íàñòîéêó ðåãèñòðîâ äëÿ ÷òåíèÿ ñåêòîðà âûáðàííîãî ðàçäåëà
	  mov di, DAP_structure
	  add di, 8
	  add si, 8
	  mov ebx, [ds:si]
	  mov [ds:di], ebx
	  mov si, DAP_structure	;÷èòàåì äèñê
	  int 13h
	  jc  ext_not_present_error

	  jmp 0000:7C00h		;ïåðåäàåì óïðàâëåíèå íà âòîðè÷íûé çàãðóç÷èê

;======== Ïîäïðîãðàììà âûâîäà ñîîáùåíèé ================================
print:
	  push si
	  push bx

	  mov bx, ax
	  xor si, si
	  mov ah, 0Eh

p:	  mov al, [bx + si]
	  cmp al, 0Ah
	  int 10h

	  je end_print

	  inc si
	  jmp p

end_print:
	  pop bx
	  pop si
	  ret

;=======================================================================
hello_msg_1	 db '************************', 0Dh, 0Ah
hello_msg_2	 db 'Simple multiboot  loader', 0Dh, 0Ah
boot_part_msg	 db 'Find bootable partitions:', 0Dh, 0Ah
select_part_msg  db 'Select part to boot from (press 0 ... 3)', 0Dh, 0Ah
wrong_input_msg  db 'Wrong choise. Try again', 0Dh, 0Ah
ext_not_pres_msg db 'a disk read error occured', 0Dh, 0Ah
part_num	 db '0', 0Dh, 0Ah
part_adr	 dw 1AEh
boot_flags	 db 0,0,0,0
DAP_structure	 db 10h, 0, 1, 0, 0, 7Ch, 0, 0, 0,0,0,0,0,0,0,0