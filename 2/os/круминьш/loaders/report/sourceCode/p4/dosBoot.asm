; Disassembly of a Microsoft FAT12/16 volume boot record, by Toby Jones.
; Disassembled around 16 March 2001.

; This code is valid for DOS boot sectors, though it is likely that modern
; boot sectors simply display an error message without attempting to load IO.SYS.

struc direntry
    .Name           resb 8
    .Extension      resb 3
    .Attributes     resb 1
    .Reserved       resb 10
    .Time           resw 1
    .Date           resw 1
    .StartCluster   resw 1
    .FileSize       resd 1
endstruc

;----------------------------------------------------------------------------
org 7c00h

start:
    jmp     short after_data
    nop

; BIOS Parameter Block ------------------------------------------------------

%define MEDIA_DESCRIPTOR_FLOPPY144_DISK 0f0h

struc bpb_fat16
    .OEMName           resb 8
    .BytesPerSector    resw 1
    .SectorsPerCluster resb 1
    .ReservedSectors   resw 1
    .FATs              resb 1
    .RootEntries       resw 1
    .Sectors           resw 1
    .MediaDescriptor   resb 1
    .FATSectors        resw 1
    .SectorsPerTrack   resw 1
    .Heads             resw 1
    .HiddenSectors     resd 1
    .HugeSectors       resd 1
    .DriveNumber       resb 1
    .Reserved          resb 1
    .BootSignature     resb 1
    .VolumeID          resd 1
    .VolumeLabel       resb 11
    .FileSystemType    resb 8
endstruc

bpb:
istruc bpb_fat16
    at bpb_fat16.OEMName,           db '        '
    at bpb_fat16.BytesPerSector,    dw 200h
    at bpb_fat16.SectorsPerCluster, db 1
    at bpb_fat16.ReservedSectors,   dw 1
    at bpb_fat16.FATs,              db 2
    at bpb_fat16.RootEntries,       dw 0e0h
    at bpb_fat16.Sectors,           dw 0b40h
    at bpb_fat16.MediaDescriptor,   db MEDIA_DESCRIPTOR_FLOPPY144_DISK
    at bpb_fat16.FATSectors,        dw 9
    at bpb_fat16.SectorsPerTrack,   dw 12h
    at bpb_fat16.Heads,             dw 2
    at bpb_fat16.HiddenSectors,     dd 0
    at bpb_fat16.HugeSectors,       dd 0
    at bpb_fat16.DriveNumber,       db 0
    ; Reserved is used by the boot code to store the next head number to read from.
    at bpb_fat16.Reserved,          db 0
    at bpb_fat16.BootSignature,     db 29h  ; Indicates the following three fields are valid.
    at bpb_fat16.VolumeID,          dd 0
    at bpb_fat16.VolumeLabel,       db '           '
    at bpb_fat16.FileSystemType,    db 'FAT12   '
iend

; Disk Parameter Table
struc dpt
    .HeadUnloadTime     resb 1
    .HeadLoadTime       resb 1
    .MotorDelayOff      resb 1
    .BytesPerSector     resb 1
    .SectorsPerTrack    resb 1
    .SectorGapLength    resb 1
    .DataLength         resb 1
    .FormatGapLength    resb 1
    .FormatByteValue    resb 1
    .HeadSettlingTime   resb 1
    .MotorDelayOn       resb 1
endstruc

struc bss_data
    .free_space_start   resd 1
    .root_dir_start     resd 1
    .cylinder           resw 1
    .sector             resb 1
endstruc

;----------------------------------------------------------------------------

after_data:
    cli                         ; Set up a standard stack frame at 0:7c00.
    xor     ax,ax
    mov     ss,ax
    mov     sp,start

    push    ss                  ; The int 1eh vector is a pointer to the Disk Parameter Table.
    pop     es
    mov     bx,1eh * 4          ; Real mode interrupt vector table (IVT) entries are 4 bytes each.
    lds     si,[ss:bx]

    push    ds                  ; The Disk Parameter Table (DPT) is likely in ROM,
    push    si                  ; so copy it out to make it mutable.
    push    ss
    push    bx
    mov     di,after_data       ; Copy DPT over the already executed boot sector code.
    mov     cx,dpt_size
    cld
    repz    movsb

    push    es
    pop     ds

    ; Update DPT with new parameters.  Setting the IVT entry must be done with interrupts disabled.
    mov     byte [di - dpt_size + dpt.HeadSettlingTime],0fh ; Set the head settling time to 15 ms.
    mov     cx,[bpb + bpb_fat16.SectorsPerTrack]            ; Store disk's sectors per track
    mov     [di - dpt_size + dpt.SectorsPerTrack],cl        ; in new DPT.
    mov     [bx + 2],ax                                     ; Set new DPT pointer in IVT entry
    mov     word [bx],after_data                            ; to 0:after_data.

    sti
    int     13h                                             ; Reset disk with new DPT parameters.
    jc      restart_boot

    xor     ax,ax
    cmp     [bpb + bpb_fat16.Sectors],ax                    ; If the number of sectors is non-zero,
    jz      .calc_root_directory_start                      ; then use that as the huge sector count.
    mov     cx,[bpb + bpb_fat16.Sectors]                    ; The sector count and huge sector count are
    mov     [bpb + bpb_fat16.HugeSectors],cx                ; not otherwise used in the boot sector.

.calc_root_directory_start:
    mov     al,[bpb + bpb_fat16.FATs]                       ; Calculate the combined size of the FAT tables
    mul     word [bpb + bpb_fat16.FATSectors]               ; in sectors.
    add     ax,[bpb + bpb_fat16.HiddenSectors]              ; Add in the count of hidden and reserved sectors
    adc     dx,[bpb + bpb_fat16.HiddenSectors + 2]          ; to determine the start of the root directory.
    add     ax,[bpb + bpb_fat16.ReservedSectors]
    adc     dx,0
    mov     [bss_section + bss_data.root_dir_start],ax      ; Save the start of the root directory.  Also save
    mov     [bss_section + bss_data.root_dir_start +2],dx   ; the start of free space, which will be updated
    mov     [bss_section + bss_data.free_space_start],ax    ; once the size of the root directory is known.
    mov     [bss_section + bss_data.free_space_start + 2],dx

    mov     ax,direntry_size                                ; Calculate the size of root directory in bytes.
    mul     word [bpb + bpb_fat16.RootEntries]

    mov     bx,[bpb + bpb_fat16.BytesPerSector]             ; Calculate the size of root directory in sectors (rounded up).
    add     ax,bx
    dec     ax
    div     bx
    add     [bss_section + bss_data.free_space_start],ax            ; Calculate the start of free space, which begins
    adc     word [bss_section + bss_data.free_space_start + 2],0    ; immediately after the root directory.

    mov     bx,500h
    mov     dx,[bss_section + bss_data.root_dir_start + 2]          ; Get the start of the root directory in CHS.
    mov     ax,[bss_section + bss_data.root_dir_start]
    call    lba_sector_to_chs
    jc      restart_boot

    mov     al,1                    ; Read in one sector of the root directory to 0:500.
    call    read_sectors
    jc      restart_boot

    ; Verify that the first two directory entries are IO.SYS and MSDOS.SYS.
    mov     di,bx                   ; Point to the first filename and ensure it is IO.SYS.
    mov     cx,8 + 3
    mov     si,iosys_string
    repz    cmpsb
    jnz     restart_boot
    lea     di,[bx + direntry_size] ; Point to the next filename and ensure it is MSDOS.SYS.
    mov     cx,8 + 3
    repz    cmpsb
    jz      load_io_sys             ; Load IO.SYS.

restart_boot:
    mov     si,emsg                 ; 'Non-System disk or disk error'...
    call    print_string            ; Print the error string.
    xor     ax,ax
    int     16h                     ; Wait for a keystroke.
    pop     si
    pop     ds
    pop     word [si]
    pop     word [si + 2]
    int     19h                     ; Reload the boot sector.
                                    ; This call does not return.

;----------------------------------------------------------------------------

stackfix_restart_boot:
    pop     ax
    pop     ax
    pop     ax
    jmp     restart_boot

;----------------------------------------------------------------------------

; bx->Root directory entry of IO.SYS.
load_io_sys:
    ; This code requires that the first three sectors of IO.SYS be contiguous.
    mov     ax,[bx + direntry.StartCluster]                 ; Get the cluster start of IO.SYS.
    dec     ax
    dec     ax
    mov     bl,[bpb + bpb_fat16.SectorsPerCluster]          ; Calculate the sector number of that cluster.
    xor     bh,bh
    mul     bx
    add     ax,[bss_section + bss_data.free_space_start]    ; Clusters begin at the start of free space.
    adc     dx,[bss_section + bss_data.free_space_start + 2]
    mov     bx,700h                                         ; Set up to read in 3 sectors of IO.SYS to 0:700.
    mov     cx,3

read_next_io_sys_sector:
    push    ax                          ; Save logical sector number (dx:ax) and currect sector count (cx).
    push    dx
    push    cx

    call    lba_sector_to_chs           ; Convert logical sector to CHS.
    jb      stackfix_restart_boot

    mov     al,1                        ; Read in one sector of IO.SYS.
    call    read_sectors

    pop     cx
    pop     dx
    pop     ax

    jb      restart_boot                ; If read failed, then print error message and reboot.

    add     ax,1                                            ; Calculate the next IO.SYS logical sector number.
    adc     dx,0
    add     bx,[bpb + bpb_fat16.BytesPerSector]             ; Calculate the next read buffer address.
    loop    read_next_io_sys_sector                         ; Loop until three sectors are read.

    ; Jump to IO.SYS, passing in parameters.
    mov     ch,[bpb + bpb_fat16.MediaDescriptor]
    mov     dl,[bpb + bpb_fat16.DriveNumber]
    mov     bx,[bss_section + bss_data.free_space_start]
    mov     ax,[bss_section + bss_data.free_space_start + 2]
    jmp     0070h:0000                  ; Jump to IO.SYS entry point.

;----------------------------------------------------------------------------

; si->The string to print.
print_string:
    lodsb                           ; Get a character.
    or      al,al                   ; If the character is null then return.
    jz      conditional_return

    mov     ah,0eh
    mov     bx,7
    int     10h                     ; Print this character.
    jmp     print_string            ; Go do the next character.

; Convert logical sector to CHS ---------------------------------------------

; dx:ax->Logical sector number to convert.
lba_sector_to_chs:
    cmp     dx,[bpb + bpb_fat16.SectorsPerTrack]        ; Fail if LBA is too large.
    jnb     .error

    div     word [bpb + bpb_fat16.SectorsPerTrack]      ; Calculate the track number.
    inc     dl                                          ; Sectors are one based.
    mov     [bss_section + bss_data.sector],dl          ; Remainder is the starting sector number.

    xor     dx,dx                                       ; Calculate final head and track/cylinder.
    div     word [bpb + bpb_fat16.Heads]
    mov     [bpb + bpb_fat16.Reserved],dl               ; Save the head number.
    mov     [bss_section + bss_data.cylinder],ax        ; Save the track number.

    clc
    retn

.error:
    stc

conditional_return:
    retn

;----------------------------------------------------------------------------

; al->The number of sectors to read.
; es:bx->Pointer to the read buffer.
read_sectors:
    mov     ah,2
    mov     dx,[bss_section + bss_data.cylinder]    ; Put the cylinder in ch, with the high
    mov     cl,6                                    ; bits (8-9) in the top of cl.  The lower six
    shl     dh,cl                                   ; bits hold the starting sector number.
    or      dh,[bss_section + bss_data.sector]
    mov     cx,dx
    xchg    ch,cl
    mov     dl,[bpb + bpb_fat16.DriveNumber]        ; Put the head number in dh, and the drive number
    mov     dh,[bpb + bpb_fat16.Reserved]           ; in dl (80h is the first fixed disk).
    int     13h                                     ; Read in the sectors.
    retn

; String Table --------------------------------------------------------------

emsg:
    db 0dh, 0ah, 'Non-System disk or disk error'
    db 0dh, 0ah, 'Replace and press any key when ready', 0dh, 0ah, 0

iosys_string:
    db 'IO      SYS'
    db 'MSDOS   SYS'
    dw 0

    dw 0aa55h

;----------------------------------------------------------------------------

; These structures are located after the BPB, and overlays the code that
; has already been executed by the time these structures are initialized.
absolute after_data
            resb dpt_size
bss_section resb bss_data_size