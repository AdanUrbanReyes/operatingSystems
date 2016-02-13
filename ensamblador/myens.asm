section .data
mensaje	db "hola mundo",0xA
longitud equ $ - mensaje
section .text
	global _start
_start:
mov edx,longitud
mov ecx,mensaje
mov ebx,1
mov eax,4
int 0x80
mov ebx,0
mov eax,1
int 0x80
;definimos el punto de entrada
;EDX=long. de la cadena
;ECX=cadena a imprimir
;EBX=manejador de fichero (STDOUT)
;EAX=función sys_write() del kernel
;interrupc. 80 (llamada al kernel)
;EBX=código de salida al SO
;EAX=función sys_exit() del kernel
;interrupc. 80 (llamada al kernel)

;segment .data
;cadena db 50
;longitud equ $ - cadena
;segment .text
;	global _start
;_start:
;	mov edx,longitud
;	mov ecx,cadena
;	mov ebx,0
;	mov eax,3
;	int 0x80
;	mov edx,longitud
;	mov ecx,cadena
;	mov ebx,1
;	mov eax,4
;	int 0x80
;	mov eax,1
;	int 0x80
