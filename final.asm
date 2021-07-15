.model flat
.stack 100h
.data

;data nhan biet cac nut-------------------------
capmsg db 10,13,"Capslock is ON, Numlock is OFF$"
nummsg db 10,13,"Numlock is ON, Capslock is OFF$"
timemsg db 10,13,"Capslock is ON, Numlock is ON$"
outmsg db 10,13,"Capslock is OFF, Numlock is OFF$"
newl db 10,13," $"

num dw ?
cap dw ?  

     
        
;data hiem thi gio------------------------------        
hour db ?  ;
mins db ?  ; 

secs db ?  ;

hour1 db ? ;
hour2 db ? ;initialize variables
min1 db ?  ;
min2 db ?  ;

sec1 db ? ;
sec2 db ? ; 



;data nhapCaplk----------------------------------
IN1 DB "MOI NHAP M: $"
OUT1 DB 0DH, 0AH, "M = $"
IN2 DB 0DH, 0AH, "MOI NHAP N: $"
OUT2 DB 0DH, 0AH, "N = $"
MSG DB 0DH, 0AH, "HINH CHU NHAT KICH THUOC MxN: ", 0DH, 0AH, '$'
M DB ?
N DB ?





;data nhapNumlk----------------------------------
tb1 db "Nhap so tu nhien thu nhat: $"
tb2 db 10,13,"Nhap so tu nhien thu hai: $"
tb3 db 10,13,"Tong 2 chu so: $"  
tb4 db 10,13,"Hieu 2 chu so: $" 
tb5 db 10,13,"Tich 2 chu so: $" 
tb6 db 10,13,"Thuong 2 chu so: $" 
x dw ?
y dw ?
temp dw ? ;bien tam giu so de hien thi ra man hinh  




.code
;---------------------ham main--------------------
main proc
    
    ;kiem tra xem nut capslock co bat, neu bat goi label nhapcap
    xor ax,ax
    mov es,ax
    mov bx,es:[417h]
    and bx,40h
    cmp bx,0
    jne nhapcap
    
    ;kiem tra xem nut numlock co bat, neu bat goi label nhapnum
    xor ax,ax
    mov es,ax
    mov bx,es:[417h]
    and bx,20h
    cmp bx,0
    jne nhapnum
    
    
    ;sau khong nut nao bat, xuat thong bao OFF/OFF va thoat
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,outmsg 
    int 21h
    
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,newl
    int 21h
    
    mov ah,4ch
    int 21h


nhapcap:
    
    ;kiem tra xem nut numlock co bat thi goi label chaygio
    xor ax,ax
    mov es,ax
    mov bx,es:[417h]
    and bx,20h
    cmp bx,0
    jne chaygio
    
    ;numlock khong bat, xuat thong bao va goi ham nhapCaplk
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,capmsg
    int 21h
    
    
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,newl
    int 21h
    
    call nhapCaplk
    
    mov ah,4ch
    int 21h
    
nhapnum:
    
    
    ;kiem tra xem nut capslock co bat thi goi label chaygio
    xor ax,ax
    mov es,ax
    mov bx,es:[417h]
    and bx,40h
    cmp bx,0
    jne chaygio
    
    ;capslock khong bat, xuat thong bao va goi ham nhapNumlk
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,nummsg
    int 21h
    
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,newl
    int 21h
    
    call nhapNumlk
    
    mov ah,4ch
    int 21h
    
    
;label goi ham time de hien thi gio ra man hinh    
chaygio:
    
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,timemsg
    int 21h
    
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,newl
    int 21h
    
    call time
    
    
    mov ah,4ch
    int 21h    
main endp  

;----------------------ham nhap khi bat nut Cap-----------------
nhapCaplk proc
    
    MOV AX, @DATA
    MOV DS, AX

    ; XUAT CHUOI "MOI NHAP M: "
    LEA DX, IN1
    MOV AH, 9
    INT 21h

    ; NHAP M
    MOV AH, 1
    INT 21h
    MOV M, AL
    
    ; XUAT CHUOI "M = " 
    LEA DX, OUT1
    MOV AH, 9
    INT 21h

    ; XUAT M
    MOV DL, M
    MOV AH, 2
    INT 21h

    ; XUAT CHUOI "MOI NHAP N: "
    LEA DX, IN2
    MOV AH, 9
    INT 21h

    ; NHAP N
    MOV AH, 1
    INT 21h
    MOV N, AL
    
    ; XUAT CHUOI "N = " 
    LEA DX, OUT2
    MOV AH, 9
    INT 21h

    ; XUAT N
    MOV DL, N
    MOV AH, 2
    INT 21h
    
    ; XUAT CHUOI "HINH CHU NHAT: " 
    LEA DX, MSG
    MOV AH, 9
    INT 21h

    ; TRU M, N VOI '0' DE RA GIA TRI DUNG
    SUB M, 48
    SUB N, 48
    
    L1: ; M LOOP
        MOV DL, '*'
        MOV BL, N ; LUU N TAM VAO BL
        XOR CX, CX
        MOV CL, BL  ; LUU N VAO CL DE SU DUNG CHO L2

        L2: ; N LOOP
            MOV AH, 2
            INT 21h
        LOOP L2

        ; SAU KHI IN 1 DONG THI XUONG HANG
        MOV DL, 0DH
        MOV AH, 2
        INT 21h

        MOV DL, 0AH
        MOV AH, 2
        INT 21h

        ; M - 1, NEU M KHAC 0 THI QUAY VE L1 
        SUB M, 1
        CMP M, 0
        JA L1
    

    ret
   
nhapCaplk endp 

     
;---------------------ham nhap khi bat nut Num------------------------     
     
     
nhapNumlk proc 
    
    mov x,0
    mov y,0  
    
    ;nhap so tu nhien dau tien x
    mov ax,@data
    mov ds,ax
    mov ah,9
    lea dx,tb1
    int 21h
    mov ah,1
    int 21h
    sub al,30h
    xor ah,ah
    mov x,ax  
            
    ;nhap so tu nhien thu hai y
    mov ah,9
    lea dx,tb2
    int 21h
    mov ah,1
    int 21h
    sub al,30h
    xor ah,ah
    mov y,ax  
    
    
    ;tinh tong va luu vao bien temp, goi ham hthi de xuat gia tri temp
    mov ah,9
    lea dx,tb3
    int 21h
    mov ax,x
    add ax,y 
    mov temp,ax
    call hthi
    
    
    ;tinh hieu va xuat gia tri
    mov ah,9
    lea dx,tb4
    int 21h
    mov ax,x
    mov bx,y
    cmp ax,bx
    jna rev   ; so sanh neu x > y thi lay y - x sau do them dau tru ( - )
    sub ax,bx ;vao ket qua
    mov dx,ax
    add dl,30h;xuat dua vao bang ASCII nen phai cong 30h de chuyen thanh chu so
    mov ah,2
    int 21h
    
    
    
    ;tinh tich luu vao bien temp, goi ham hthi de xuat gia tri temp
tich:
    mov ax,x
    mul y
    mov temp,ax
    mov ah,9
    lea dx,tb5
    int 21h
    call hthi
    
    
    
    ;tinh thuong va xuat gia tri
    mov ah,9
    lea dx,tb6
    int 21h
    mov bx,y
    mov ax,x
    div bl  
    
    
    mov bh,ah ;dung bh luu gia tri du khi chia 
    
    
    mov dl,al
    add dl,30h
    mov ah,2
    int 21h
    cmp bh,0
    je thoatra ;neu du = 0 thi thoat
    
;hien thi dau cham ( . )    
real:
    mov ah,2
    mov dl,46
    int 21h 
    
;xuat cac chu so sau dau cham ( . )   
divide:

    ; so du sau moi lan chia sau lan dau se nhan 10 len va tiep tuc chia
    ;de lay so nguyen va so du
    xor ax,ax
    mov al,bh
    xor bx,bx
    mov bx,10
    mul bx
    mov bx,y
    div bl
    mov bh,ah
    mov dl,al
    add dl,30h  ;so nguyen se hien thi ra ngoai
    mov ah,2
    int 21h
    cmp bh,0   ;van con so du thi tiep tuc nhan 10 va chia
    jne divide
thoatra:
    ret 
   
rev:
    sub bx,ax
    mov dl,45
    mov ah,2
    int 21h
    mov dx,bx
    add dl,30h
    mov ah,2
    int 21h
    jmp tich    
nhapNumlk endp 

;-------------------ham hien thi so nguyen > 2 chuso--------------------

;la ham chuyen so hex trong temp thanh deci roi xuat ra ngoai    
hthi proc
    mov bx,10
    mov ax,temp
    mov cx,0

chia:

    ;chia lay phan du bo vo stack, lay phan nguyen tiep tuc chia
    mov dx,0
    div bx
    inc cx      ;cx dem so lan chia de biet can xuat bao nhieu chu so
    push dx
    cmp al,0    ;chia den khi nao so nguyen = 0
    je ht
    jmp chia
ht: 

    ;xuat lan luot cac phan tu trong stack ra theo LIFO
    pop dx 
    add dl,30h
    mov ah,2
    int 21h
    dec cx ;chay nguoc cx de xuat bao nhieu chu so
    cmp cx,0
    jne ht
    ret 
hthi endp




;------------------ham hien thi thoi gian--------------------------------
time proc
    
    mov ah, 2ch   ;get time
    int 21h       ;

    mov hour, ch  
    mov mins, cl
    mov secs, dh

    mov ah, 0     ;
    mov al, hour  ;divide by 10
    mov bl, 10    ;
    div bl        ;

    mov hour1, al 
    mov hour2, ah 

    mov ah, 2     ;
    mov dl, hour1 ;  
    add dl, 30h   ;
    int 21h       ;
                ;print hour
    mov ah, 2     ;
    mov dl, hour2 ;
    add dl, 30h   ;
    int 21h       ;

    mov ah, 2     
    mov dl, ':'   
    int 21h       

    mov ah, 0     ;
    mov al, mins  ;divide by 10
    mov bl, 10    ;
    div bl        ;

    mov min1, al  
    mov min2, ah  

    mov ah, 2     ;
    mov dl, min1  ; 
    add dl, 30h   ;
    int 21h       ;
                ;print minuntes
    mov ah, 2     ;
    mov dl, min2  ;
    add dl, 30h   ;
    int 21h       ;

    mov ah, 2     
    mov dl, ':'   
    int 21h  

    mov ah, 0     ;
    mov al, secs  ;divide by 10
    mov bl, 10    ;
    div bl        ;

    mov sec1, al 
    mov sec2, ah 

    mov ah, 2     ;
    mov dl, sec1  ;  
    add dl, 30h   ;
    int 21h       ;
                ; print seconds
    mov ah, 2     ;
    mov dl, sec2  ;
    add dl, 30h   ;
    int 21h       ;

    ret
time endp
end main                     