segment .data						;Segmento de datos
cadena db 'Programado en ensamblador para linux',0xA    ;Cadena a imprimir
segment .text						;Segmento de codigo
	global _start					;Punto de entrada al programa (Usado con el enlazador Id)
_start: 						;Inicio de programa
	mov edx,38 					;Longitud de cadena
	mov ecx,cadena					;Cadena a escrivir
	mov ebx,1					;Salida estandar
	mov eax,4					;Numero de llamda al sistema sys_write
	int 0x80					;Interrupcion de llamadas al sistema del kernel de linuk
	mov eax,1					;Numero de llamdas al sistema sys_exit
	int 0x80 					;Interrupcion de llamdas al sistema del kernel de Linux
